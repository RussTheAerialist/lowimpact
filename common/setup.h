#pragma once
#include "arduino.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_10DOF.h>

void common_setup(Adafruit_NeoPixel &strip,
       Adafruit_LSM303_Accel_Unified &accel,
       Adafruit_LSM303_Mag_Unified &mag,
       Adafruit_BMP085_Unified &bmp,
       int program_number = 0
);

