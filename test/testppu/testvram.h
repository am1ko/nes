#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ppu.h"
#include "mockmemory.h"
#include "mockrenderer.h"

class PpuVramTest : public ::testing::Test {

protected:

    PpuVramTest();
    virtual ~PpuVramTest();

    Ppu ppu;
    MockMemory bus;
    MockMemory oam;
    MockRenderer renderer;
};
