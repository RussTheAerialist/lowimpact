#include <stdint.h>
#include "arduino.h"
#include <Adafruit_Neopixel.h>
#include "pixel.h"
#include "accel.h"
#include "color.h"
#include "setup.h"

void hsv_pulse(RGBPixel &pixel, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta)
{
  static HSVPixel hsvpix;
  static RGBPixel rgbpix;

  hsvpix.hue = map_accel(x_delta, 255);
  hsvpix.value = map_accel(y_delta, 255);
  hsvpix.saturation = map_accel(z_delta, 255);

  hsvpix.loadTo(&rgbpix);

  avg_color(pixel,
            rgbpix.red,
            rgbpix.green,
            rgbpix.blue
           );
}

void rgb_3_pulse(RGBPixel &frame0, RGBPixel &frame1, RGBPixel &frame2, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta) {

  avg_color(frame0,
            map_accel(x_delta, 255),
            frame0.green,
            frame0.blue
           );

  avg_color(frame1,
            frame1.red,
            map_accel(y_delta, 255),
            frame1.blue
           );

  avg_color(frame2,
            frame2.red,
            frame2.green,
            map_accel(z_delta, 255)
           );
}

void rgb_pulse(RGBPixel &frame, uint8_t x_delta, uint8_t y_delta, uint8_t z_delta) {
  avg_color(frame,
    map_accel(x_delta, 255),
    map_accel(y_delta, 255),
    map_accel(z_delta, 255));
}

void avg_color(RGBPixel &pixel,
                      uint8_t r,
                      uint8_t g,
                      uint8_t b
                     )
{
  r = (pixel.red * AVERAGE_FACTOR + r) / (AVERAGE_FACTOR + 1);
  g = (pixel.green * AVERAGE_FACTOR + g) / (AVERAGE_FACTOR + 1);
  b = (pixel.blue * AVERAGE_FACTOR + b) / (AVERAGE_FACTOR + 1);

  if (r < 0) r = 0; else if (r > 0xFF) r = 0xFF;
  if (g < 0) g = 0; else if (g > 0xFF) g = 0xFF;
  if (b < 0) b = 0; else if (b > 0xFF) b = 0xFF;

  pixel.red = r;
  pixel.green = g;
  pixel.blue = b;
}

void avg_color(RGBPixel &pixel, RGBPixel &newpix)
{
  avg_color(pixel, newpix.red, newpix.green, newpix.blue);
}

static void fade_pixel(Adafruit_NeoPixel& strip, RGBPixel* frame, int x, int numPixels) {
  uint32_t color = strip.getPixelColor((x + 1) % numPixels);
  avg_color(frame[x], color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
  color = strip.getPixelColor((x - 1) % numPixels);
  avg_color(frame[x], color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
}

void strip_fade(Adafruit_NeoPixel& strip, RGBPixel* frame) {
  int numPixels = strip.numPixels();
  for (int i = 0; i < numPixels; i++) {
    fade_pixel(strip, frame, i, numPixels);
  }
}