#include <stdint.h>
#include "pixel.h"
#include "color.h"

void hsv_pulse(RGBPixel &pixel, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta)
{
  static HSVPixel hsvpix;
  static RGBPixel rgbpix;

  hsvpix.hue = map(x_delta, 0, maxAcceleration, 0, 255);
  hsvpix.value = map(y_delta, 0, maxAcceleration, 0, 255);
  hsvpix.saturation = map(z_delta, 0, maxAcceleration, 0, 255);

  hsvpix.loadTo(&rgbpix);

  avg_color(pixel,
            rgbpix.red,
            rgbpix.green,
            rgbpix.blue
           );
}

void avg_color(RGBPixel &pixel,
                      int r,
                      int g,
                      int b
                     )
{
  if (x < 0 || x >= NUM_PIXELS)
    return;

  r = (pixel->red * 3 + r) / 4;
  g = (pixel->green * 3 + g) / 4;
  b = (pixel->blue * 3 + b) / 4;

  if (r < 0) r = 0; else if (r > 0xFF) r = 0xFF;
  if (g < 0) g = 0; else if (g > 0xFF) g = 0xFF;
  if (b < 0) b = 0; else if (b > 0xFF) b = 0xFF;

  pixel->red = r;
  pixel->green = g;
  pixel->blue = b;
}
