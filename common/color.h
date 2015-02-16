#pragma once

#include <stdint.h>

class RGBPixel;

void hsv_pulse(RGBPixel &pixel, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta);
void rgb_3_pulse(RGBPixel &frame0, RGBPixel &frame1, RGBPixel &frame2, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta);

void avg_color(RGBPixel &pixel, uint8_t r, uint8_t g, uint8_t b);
void avg_color(RGBPixel &pixel, RGBPixel &newpix);
