#ifndef RENDERER_H
#define RENDERER_H

struct Renderer {
    virtual void prepare() = 0;
    virtual void draw_pixel(uint16_t x, uint16_t y, uint8_t color) = 0;
    virtual void flush() = 0;
};

#endif
