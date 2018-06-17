#ifndef MOCK_RENDERER_H
#define MOCK_RENDERER_H

#include "gmock/gmock.h"
#include "renderer.h"

struct MockRenderer: public Renderer
{
    MOCK_METHOD3(draw_pixel, void(uint16_t x, uint16_t y, uint8_t color));
    MOCK_METHOD0(flush, void());
};

#endif
