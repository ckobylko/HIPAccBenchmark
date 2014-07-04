#pragma once

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
#endif

HIPACC_SET_INPUT_PIXEL_TYPE_1( float );
HIPACC_SET_OUTPUT_PIXEL_TYPE ( unsigned char );

