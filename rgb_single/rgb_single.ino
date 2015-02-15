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

class RGBPixel
{
  public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

const float seaLevelPressure PROGMEM = SENSORS_PRESSURE_SEALEVELHPA;
const int maxAcceleration PROGMEM = 10;
Adafruit_10DOF dof = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);

sensors_event_t accel_event_1, mag_event, bmp_event, accel_event_2;
sensors_vec_t orientation;
bool which = false;

#define PIN 6
#define NUM_PIXELS 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
RGBPixel frame[NUM_PIXELS];

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();

  // Init Sensors
  bool successful = accel.begin() && mag.begin() && bmp.begin();

  if (!successful) {
    Serial.println("Check your wiring!");
    strip.setPixelColor(4, 128, 0, 0);
    strip.show();
    while (1);
  }
  Serial.println("Beginning");
}

void pulse(int x, sensors_event_t *event, sensors_event_t *previous_event)
{
  int8_t x_delta = abs(event->acceleration.x - previous_event->acceleration.x);
  int8_t y_delta = abs(event->acceleration.y - previous_event->acceleration.y);
  int8_t z_delta = abs(event->acceleration.z - previous_event->acceleration.z);

  avg_color(x,
            map(x_delta, 0, maxAcceleration, 0, 255),
            map(y_delta, 0, maxAcceleration, 0, 255),
            map(z_delta, 0, maxAcceleration, 0, 255)
           );
}

void loop() {
  sensors_event_t *event = which ? &accel_event_1 : &accel_event_2;
  accel.getEvent(event);
  mag.getEvent(&mag_event);

  if (dof.fusionGetOrientation(event, &mag_event, &orientation)) {
    Serial.print("X: "); Serial.print(event->acceleration.x); Serial.print(", ");
    Serial.print("Y: "); Serial.print(event->acceleration.y); Serial.print(", ");
    Serial.print("Z: "); Serial.println(event->acceleration.z);

    if (which) {
      pulse(3, &accel_event_1, &accel_event_2);
    } else {
      pulse(4, &accel_event_2, &accel_event_1);
    }

    which = !which;

    bmp.getEvent(&bmp_event);
    if (bmp_event.pressure) {
      float temperature;
      bmp.getTemperature(&temperature);
      bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, temperature);
    }
  }
  strip_fade();

  for (int i = 0; i < NUM_PIXELS; i++) {
    RGBPixel * const p = &frame[i];
    strip.setPixelColor(i, p->red, p->green, p->blue);
  }

  strip.show();
  delay(50);
}

void strip_fade() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    fade_pixel(i);
  }
}

static void fade_pixel(int x) {
  uint32_t color = strip.getPixelColor((x + 1) % NUM_PIXELS);
  avg_color(x, color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
  color = strip.getPixelColor((x - 1) % NUM_PIXELS);
  avg_color(x, color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
}

static void avg_color(int x,
                      int r,
                      int g,
                      int b
                     )
{
  if (x < 0 || x >= NUM_PIXELS)
    return;
  RGBPixel * const p = &frame[x];

  r = (p->red * 3 + r) / 4;
  g = (p->green * 3 + g) / 4;
  b = (p->blue * 3 + b) / 4;

  if (r < 0) r = 0; else if (r > 0xFF) r = 0xFF;
  if (g < 0) g = 0; else if (g > 0xFF) g = 0xFF;
  if (b < 0) b = 0; else if (b > 0xFF) b = 0xFF;

  p->red = r;
  p->green = g;
  p->blue = b;
}
