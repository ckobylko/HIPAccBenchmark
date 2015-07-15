#include "ConvolutionUInt8Handlers.h"

namespace AVX {
#include "ccConvUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList ConvolutionUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ConvolutionUInt8Handler::Create< ConvolutionUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



