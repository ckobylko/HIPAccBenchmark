#include "TopologicalErosionFloatHandlers.h"

namespace AVX {
#include "ccTopErosionFloat_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList TopologicalErosionFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( TopologicalErosionFloatHandler::Create< TopologicalErosionFloatHandler_AVX >() );

  return std::move( lstHandlers );
}



