#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include "ram.h"
#include "rom.h"
#include "ines_parser_ifstream.h"
#include "io_registers.h"
#include "bus.h"
#include "cpu.h"
#include "ppu.h"
#include "emu.h"
#include "bus_ppu.h"
#include "renderer.h"

#include "SDL2/SDL.h"
#undef main   // deal with #define main SDL_main from within SDL.h

static unsigned ppu_cycles;

// ---------------------------------------------------------------------------------------------- //
constexpr std::array<std::array<uint8_t, 3>, 64> rgb_palette = {{
{{ 84,  84,  84}}, {{  0,  30, 116}}, {{  8,  16, 144}}, {{ 48,   0, 136}}, {{ 68,   0, 100}},
{{ 92,   0,  48}}, {{ 84,   4,   0}}, {{ 60,  24,   0}}, {{ 32,  42,   0}}, {{  8,  58,   0}},
{{  0,  64,   0}}, {{  0,  60,   0}}, {{  0,  50,  60}}, {{  0,   0,   0}}, {{  0,   0,   0}},
{{  0,   0,   0}}, {{152, 150, 152}}, {{  8,  76, 196}}, {{ 48,  50, 236}}, {{ 92,  30, 228}},
{{136,  20, 176}}, {{160,  20, 100}}, {{152,  34,  32}}, {{120,  60,   0}}, {{ 84,  90,   0}},
{{ 40, 114,   0}}, {{  8, 124,   0}}, {{  0, 118,  40}}, {{  0, 102, 120}}, {{  0,   0,   0}},
{{  0,   0,   0}}, {{  0,   0,   0}}, {{236, 238, 236}}, {{ 76, 154, 236}}, {{120, 124, 236}},
{{176,  98, 236}}, {{228,  84, 236}}, {{236,  88, 180}}, {{236, 106, 100}}, {{212, 136,  32}},
{{160, 170,   0}}, {{116, 196,   0}}, {{ 76, 208,  32}}, {{ 56, 204, 108}}, {{ 56, 180, 204}},
{{ 60,  60,  60}}, {{  0,   0,   0}}, {{  0,   0,   0}}, {{236, 238, 236}}, {{168, 204, 236}},
{{188, 188, 236}}, {{212, 178, 236}}, {{236, 174, 236}}, {{236, 174, 212}}, {{236, 180, 176}},
{{228, 196, 144}}, {{204, 210, 120}}, {{180, 222, 120}}, {{168, 226, 144}}, {{152, 226, 180}},
{{160, 214, 228}}, {{160, 162, 160}}, {{  0,   0,   0}}, {{  0,   0,   0}}
}};


// ---------------------------------------------------------------------------------------------- //
struct NES_SDL_Renderer : public Renderer {
    SDL_Surface * sdl_surface;
    SDL_Window * sdl_window;
    NES_SDL_Renderer(SDL_Window * window) : sdl_window(window) {
        sdl_surface = SDL_GetWindowSurface(window);
    }

    // ------------------------------------------------------------------------------------------ //
    void prepare() {
		SDL_Rect rect;
        rect.x = rect.y = 0;
        rect.w = 256;
        rect.h = 240;

        SDL_FillRect(sdl_surface, &rect, 0xFF000000U);
    }

    // ------------------------------------------------------------------------------------------ //
    void draw_pixel(uint16_t x, uint16_t y, uint8_t color) {
        ((uint32_t*)sdl_surface->pixels)[(y*256 + x)] = rgb_palette[color][0] << 16 |
                                                      rgb_palette[color][1] << 8 | rgb_palette[color][2];
    }

    // ------------------------------------------------------------------------------------------ //
    void flush() {
        SDL_UpdateWindowSurface(sdl_window);
    }
};

// ---------------------------------------------------------------------------------------------- //
class StdOutLogger : public ICpuLogger {
public:
    void log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
             struct CpuContext const * const context);
};

// ---------------------------------------------------------------------------------------------- //
void StdOutLogger::log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
                       struct CpuContext const * const context) {
    std::cout << boost::format("%04X  ") % instr_addr;

    for (int i = 0; i < 3; i++) {
        if (bytes > i) {
            std::cout << boost::format("%02X ") % static_cast<int>(instr[i]);
        } else {
            std::cout << "   ";
        }
    }

    // TODO(amiko): disassembly
    std::cout << boost::format("%-20s") % "";

    std::cout << boost::format("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%3u \n")
    % static_cast<int>(context->sregs[A]) % static_cast<int>(context->sregs[X])
    % static_cast<int>(context->sregs[Y]) % static_cast<int>(context->P)
    % static_cast<int>(context->SP) % (ppu_cycles);
}

static constexpr std::size_t CPU_RAM_SIZE = (2*1024);
static constexpr std::size_t PPU_RAM_SIZE = (2*1024);
static constexpr std::size_t OAM_SIZE     = (256);
static constexpr std::size_t PAL_RAM_SIZE = 32;

static std::array<uint8_t, CPU_RAM_SIZE> cpu_ram_storage;
static std::array<uint8_t, PPU_RAM_SIZE> ppu_ram_storage;
static std::array<uint8_t, PAL_RAM_SIZE> pal_ram_storage;
static std::array<uint8_t, CHR_ROM_SIZE> chr_rom_storage;
static std::array<uint8_t, PRG_ROM_SIZE> prg_rom_storage_lower;
static std::array<uint8_t, PRG_ROM_SIZE> prg_rom_storage_upper;
static std::array<uint8_t, OAM_SIZE>     oam_storage;

// ---------------------------------------------------------------------------------------------- //
int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window =
            SDL_CreateWindow("YANES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 240, 0);

    // ------------------------------------------------------------------------------------------ //
    assert(argc == 2);
    std::string file = std::string(argv[1]);

    ROM <PRG_ROM_SIZE> prg_rom_lower(prg_rom_storage_lower);
    ROM <PRG_ROM_SIZE> prg_rom_upper(prg_rom_storage_upper);
    ROM <CHR_ROM_SIZE> chr_rom(chr_rom_storage);
    RAM <CPU_RAM_SIZE> cpu_ram(cpu_ram_storage);
    RAM <PPU_RAM_SIZE> ppu_ram(ppu_ram_storage);
    RAM <PAL_RAM_SIZE> pal_ram(pal_ram_storage);
    RAM <OAM_SIZE>     oam(oam_storage);

    {
        INES_parser_ifstream ines_parser(file);

        assert(ines_parser.num_prg_rom_banks < 3);
        assert(ines_parser.num_chr_rom_banks == 1);

        ines_parser.write_chr_rom(0U, chr_rom_storage);
        ines_parser.write_prg_rom(0U, prg_rom_storage_lower);

        if (ines_parser.num_prg_rom_banks == 2) {
            ines_parser.write_prg_rom(1U, prg_rom_storage_upper);
        }
        else {
            ines_parser.write_prg_rom(0U, prg_rom_storage_upper);
        }
    }

    NES_SDL_Renderer renderer(window);
    IO_Registers io_registers;
    BusPpu ppu_bus(ppu_ram, pal_ram, chr_rom);
    Ppu ppu(ppu_bus, oam, renderer);
    Bus bus(cpu_ram, prg_rom_lower, prg_rom_upper, ppu, io_registers);
    Cpu cpu(bus);
    Emu emu(cpu, ppu);

    emu.reset();

    // ------------------------------------------------------------------------------------------ //

    bool quit = false;

    while (!quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                break;
            }
        }

        unsigned ret;

        while(1) {
            ret = emu.tick();

            unsigned ppu_cycles_old = ppu_cycles;
            ppu_cycles = (ppu_cycles + ret*3U) % 341U;
            if (ppu_cycles < ppu_cycles_old) break;;
        }

        if (ret == 0) {
            std::cout << "Unknown instruction" << std::endl;
            break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
