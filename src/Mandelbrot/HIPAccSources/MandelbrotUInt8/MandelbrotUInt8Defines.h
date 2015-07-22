#ifndef _MANDELBROT_UINT8_DEFINES_H_
#define _MANDELBROT_UINT8_DEFINES_H_

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
#endif

HIPACC_SET_PIXEL_TYPE  ( unsigned char );

#endif // _MANDELBROT_UINT8_DEFINES_H_
