#include <Adafruit_NeoPixel.h>

#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_10DOF.h>

#include "setup.h"
#include "pixel.h"
#include "color.h"
#include "accel.h"

#define MAIN_AXIS y
#define MAIN_DELTA y_delta
#define MAIN_AXIS_VALUE(XX) XX.acceleration.MAIN_AXIS
#define AXIS_ORIENTATION <=
#define THRESHOLD -5

const float seaLevelPressure PROGMEM = SENSORS_PRESSURE_SEALEVELHPA;
Adafruit_10DOF dof = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);

sensors_event_t accel_event, mag_event, bmp_event, accel_event_avg;
sensors_vec_t orientation;
bool which = false;
uint8_t count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
RGBPixel frame[NUM_PIXELS];

void setup() {
  common_setup(strip, accel, mag, bmp, Programs::avgAmbientThreshold);
}

void pulse(int x, int8_t x_delta, int8_t y_delta, int8_t z_delta)
{

  rgb_3_pulse(frame[x], frame[FIRST_PIXEL], frame[LAST_PIXEL],
    abs(x_delta), abs(y_delta), abs(z_delta)
    );
  rgb_3_pulse(frame[x+1], frame[FIRST_PIXEL+1], frame[LAST_PIXEL-1],
    abs(x_delta), abs(y_delta), abs(z_delta)
    );
}

void average(sensors_event_t *avg, sensors_event_t *event) {

  avg->acceleration.x += event->acceleration.x;
  avg->acceleration.y += event->acceleration.y;
  avg->acceleration.z += event->acceleration.z;

  count++;

  if (count == 24) {
    
    avg->acceleration.x /= 24;
    avg->acceleration.y /= 24;
    avg->acceleration.z /= 24;

    count = 1;
  }
}

void loop() {
  sensors_event_t *event = &accel_event;
  accel.getEvent(event);
  mag.getEvent(&mag_event);

  if (dof.fusionGetOrientation(event, &mag_event, &orientation)) {
      int8_t x_delta = max(0, accel_event.acceleration.x - accel_event_avg.acceleration.x/count);
      int8_t y_delta = max(0, accel_event.acceleration.y - accel_event_avg.acceleration.y/count);
      int8_t z_delta = max(0, accel_event.acceleration.z - accel_event_avg.acceleration.z/count);

      average(&accel_event_avg, &accel_event);
      which = (MAIN_AXIS_VALUE(accel_event_avg)/count AXIS_ORIENTATION THRESHOLD);

      if (which) {
          pulse(MIDDLE_PIXEL, x_delta, y_delta, z_delta);
      }
  }


  strip_fade(strip, frame);

  for (int i = 0; i < NUM_PIXELS; i++) {
    RGBPixel * const p = &frame[i];
    strip.setPixelColor(i, p->red, p->green, p->blue);
  }

  strip.show();
  delay(50);
}

