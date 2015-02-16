#pragma once

class RGBPixel
{
  public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class HSVPixel
{
  public:
    uint8_t hue;
    uint8_t saturation;
    uint8_t value;

    void loadTo(RGBPixel *pix);
};
