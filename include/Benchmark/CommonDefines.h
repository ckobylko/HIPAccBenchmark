#ifndef _BENCHMARK_COMMON_DEFINES_H_
#define _BENCHMARK_COMMON_DEFINES_H_

#define HIPACC_SET_INPUT_PIXEL_TYPE_1(__type)   typedef __type InputPixelType_1;
#define HIPACC_SET_INPUT_PIXEL_TYPE_2(__type)   typedef __type InputPixelType_2;
#define HIPACC_SET_OUTPUT_PIXEL_TYPE(__type)    typedef __type OutputPixelType;

#define HIPACC_SET_IMAGE_WIDTH(__width)     const int ciImageWidth  = __width;
#define HIPACC_SET_IMAGE_HEIGHT(__height)   const int ciImageHeight = __height;

#define HIPACC_SET_PIXEL_TYPE(__type) \
  HIPACC_SET_INPUT_PIXEL_TYPE_1(__type) \
  HIPACC_SET_INPUT_PIXEL_TYPE_2(__type) \
  HIPACC_SET_OUTPUT_PIXEL_TYPE(__type)


#define CONFIG_USE_COMMON_IMAGE_SIZE  // TODO: Uncomment this for a globally set image size
//#define CONFIG_CHECK_OUTPUT           // TODO: Uncomment this for a consistency check of the output images (they will be stored, too)



#ifdef CONFIG_USE_COMMON_IMAGE_SIZE

#ifdef CONFIG_CHECK_OUTPUT
HIPACC_SET_IMAGE_WIDTH ( 512 );
HIPACC_SET_IMAGE_HEIGHT( 512 );
#define TEST_RUN_COUNT  1
#else
HIPACC_SET_IMAGE_WIDTH ( 4096 );
HIPACC_SET_IMAGE_HEIGHT( 4096 );
#endif // CONFIG_CHECK_OUTPUT

#endif // CONFIG_USE_COMMON_IMAGE_SIZE

#endif // _BENCHMARK_COMMON_DEFINES_H_
