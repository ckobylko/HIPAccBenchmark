#include "MandelbrotUInt8Handlers.h"

namespace AVX {
#include "ccMandelbrotUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList MandelbrotUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



