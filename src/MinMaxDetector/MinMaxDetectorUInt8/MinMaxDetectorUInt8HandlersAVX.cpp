#include "MinMaxDetectorUInt8Handlers.h"

namespace AVX {
#include "ccMinMaxUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList MinMaxDetectorUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MinMaxDetectorUInt8Handler::Create< MinMaxDetectorUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



