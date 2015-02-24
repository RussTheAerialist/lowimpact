#pragma once

#include <stdint.h>

enum class Programs : uint8_t {
	undefined = 0,
    rgbSingle = 1,
    rgb3Pixel = 2,
    hsvSingle = 3,
    avgAmbient = 4,
    avgAmbientThreshold = 5
};
