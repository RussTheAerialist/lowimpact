#include "arduino.h"
#include "setup.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>

static void display_program(Adafruit_NeoPixel &strip, int program_number) {
  for(int i=0; i<strip.numPixels() && program_number > 0; i++) {
    if (program_number & 0x01) {
      strip.setPixelColor(i, 64, 64, 64);
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }

    program_number = program_number >> 1;
  }

  strip.show();
  delay(1000);
  strip.clear();
  strip.show();
}

void common_setup(
       Adafruit_NeoPixel &strip,
       Adafruit_LSM303_Accel_Unified &accel,
       Adafruit_LSM303_Mag_Unified &mag,
       Adafruit_BMP085_Unified &bmp,
       int program_number 
) {
  strip.begin();
  // strip.setBrightness(128);
  strip.show();

  // Init Sensors
  bool successful = accel.begin() && mag.begin() && bmp.begin();

  if (!successful) {
    while (1) {
      strip.setPixelColor(3, 0, 0 , 0);
      strip.setPixelColor(4, 128, 0, 0);
      strip.show();
      delay(500);
      strip.setPixelColor(3, 128, 0, 0);
      strip.setPixelColor(4, 0, 0, 0);
      strip.show();
      delay(500);
    }
  }

  if (program_number > 0) {
    display_program(strip, program_number);
  }
}

