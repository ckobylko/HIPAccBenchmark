#ifndef _NORM_GRAD_FLOAT_DEFINES_H_
#define _NORM_GRAD_FLOAT_DEFINES_H_

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 4096 );
HIPACC_SET_IMAGE_HEIGHT( 2048 );
#endif

HIPACC_SET_PIXEL_TYPE( float );

#endif // _NORM_GRAD_FLOAT_DEFINES_H_
