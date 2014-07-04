#pragma once

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
#endif

HIPACC_SET_PIXEL_TYPE  ( unsigned char );


inline InputPixelType_1 min(InputPixelType_1 a, InputPixelType_1 b)   { return (a < b) ? a : b; }
inline InputPixelType_1 max(InputPixelType_1 a, InputPixelType_1 b)   { return (a > b) ? a : b; }


