#ifndef _MANDELBROT_FLOAT_DEFINES_H_
#define _MANDELBROT_FLOAT_DEFINES_H_

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 2048 );
HIPACC_SET_IMAGE_HEIGHT( 1024 );
#endif

HIPACC_SET_PIXEL_TYPE  ( float );

#endif // _MANDELBROT_FLOAT_DEFINES_H_
