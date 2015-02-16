#include "arduino.h"
#include "setup.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>

void common_setup(
       Adafruit_NeoPixel &strip,
       Adafruit_LSM303_Accel_Unified &accel,
       Adafruit_LSM303_Mag_Unified &mag,
       Adafruit_BMP085_Unified &bmp 
) {
  strip.begin();
  strip.setBrightness(128);
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
}

