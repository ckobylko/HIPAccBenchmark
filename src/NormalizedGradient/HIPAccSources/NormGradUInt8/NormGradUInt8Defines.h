#pragma once

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 4096 );
HIPACC_SET_IMAGE_HEIGHT( 2048 );
#endif

HIPACC_SET_INPUT_PIXEL_TYPE_1 ( unsigned char )
HIPACC_SET_INPUT_PIXEL_TYPE_2 ( unsigned char )
HIPACC_SET_OUTPUT_PIXEL_TYPE  ( float )

