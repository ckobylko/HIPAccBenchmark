#ifndef _TOP_EROSION_FLOAT_DEFINES_H_
#define _TOP_EROSION_FLOAT_DEFINES_H_

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
#endif

HIPACC_SET_PIXEL_TYPE  ( float );

inline InputPixelType_1 min(InputPixelType_1 a, InputPixelType_1 b)   { return (a < b) ? a : b; }

#endif // _TOP_EROSION_FLOAT_DEFINES_H_
