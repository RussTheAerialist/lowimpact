#pragma once
#include "arduino.h"
#include "programs.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_10DOF.h>
#include <stdint.h>

////////////////////////////////////
// Configuration Section
////////////////////////////////////

#define PIN 6
#define NUM_PIXELS 14
const int FIRST_PIXEL = NUM_PIXELS / 8.0;
const int MIDDLE_PIXEL = NUM_PIXELS / 2.0;
const int LAST_PIXEL = NUM_PIXELS / 8.0 * 7.0;
#define AVERAGE_FACTOR 2

////////////////////////////////////

void common_setup(Adafruit_NeoPixel &strip,
       Adafruit_LSM303_Accel_Unified &accel,
       Adafruit_LSM303_Mag_Unified &mag,
       Adafruit_BMP085_Unified &bmp,
       Programs program_number = Programs::undefined
);

