#include "ConvolutionFloatHandlers.h"

namespace AVX {
#include "ccConvFloat_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList ConvolutionFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_AVX >() );

  return std::move( lstHandlers );
}



