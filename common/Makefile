PROJECT_DIR=$(CURDIR)
ARDMK_DIR=$(PROJECT_DIR)/../build
ARDUINO_DIR=/Applications/Arduino.app/Contents/Resources/Java

USER_LIB_PATH := $(HOME)/Documents/Arduino/libraries/
BOARD_TAG = pro
BOARD_SUB=16MHzatmega328
MONITOR_BAUDRATE = 115200
AVR_TOOLS_DIR = /usr/local
AVRDDUDE = /usr/local/bin/avrdude
CFLAGS_STD = -std=gnu11
CXXFLAGS_STD = -std=gnu++11
CXXFLAGS += -Wall

ARDUINO_LIBS = Wire Wire/utility       \
               SPI                     \
               Adafruit_NeoPixel       \
               Adafruit_Sensor         \
               Adafruit_LSM303DLHC     \
               Adafruit_L3GD20_U       \
               Adafruit_BMP085_Unified \
               Adafruit_10DOF
MONITOR_PORT = /dev/tty.usbmodem*
CURRENT_DIR = $(shell basename $(CURDIR))

OBJDIR = $(PROJECT_DIR)/../bin/$(BOARD_TAG)/$(CURRENT_DIR)

include $(ARDMK_DIR)/Arduino.mk
