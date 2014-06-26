#pragma once

#define HIPACC_SET_INPUT_PIXEL_TYPE_1(__type)   typedef __type InputPixelType_1;
#define HIPACC_SET_INPUT_PIXEL_TYPE_2(__type)   typedef __type InputPixelType_2;
#define HIPACC_SET_OUTPUT_PIXEL_TYPE(__type)    typedef __type OutputPixelType;

#define HIPACC_SET_IMAGE_WIDTH(__width)     const int ciImageWidth  = __width;
#define HIPACC_SET_IMAGE_HEIGHT(__height)   const int ciImageHeight = __height;

#define HIPACC_SET_PIXEL_TYPE(__type) \
  HIPACC_SET_INPUT_PIXEL_TYPE_1(__type) \
  HIPACC_SET_INPUT_PIXEL_TYPE_2(__type) \
  HIPACC_SET_OUTPUT_PIXEL_TYPE(__type)


#define IGNORE_ARRAY_EXPORT   // TODO: Uncomment this if the "array" exporter shall not be included in the benchmark
