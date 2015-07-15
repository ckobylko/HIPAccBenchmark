#include "TopologicalErosionUInt8Handlers.h"

namespace AVX {
#include "ccTopErosionUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList TopologicalErosionUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( TopologicalErosionUInt8Handler::Create< TopologicalErosionUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



