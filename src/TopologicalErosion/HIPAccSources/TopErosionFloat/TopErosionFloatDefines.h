#pragma once

#include "../../../../include/Benchmark/CommonDefines.h"

HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
HIPACC_SET_PIXEL_TYPE  ( float );

inline InputPixelType_1 min(InputPixelType_1 a, InputPixelType_1 b)   { return (a < b) ? a : b; }

