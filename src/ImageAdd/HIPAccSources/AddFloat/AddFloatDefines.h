#ifndef _ADD_FLOAT_DEFINES_H_
#define _ADD_FLOAT_DEFINES_H_

#include "../../../../include/Benchmark/CommonDefines.h"

#ifndef CONFIG_USE_COMMON_IMAGE_SIZE
HIPACC_SET_IMAGE_WIDTH ( 8192 );
HIPACC_SET_IMAGE_HEIGHT( 4096 );
#endif

HIPACC_SET_PIXEL_TYPE( float );

#endif // _ADD_FLOAT_DEFINES_H_
