#include "MinMaxDetectorFloatHandlers.h"

namespace AVX {
#include "ccMinMaxFloat_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList MinMaxDetectorFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_AVX >() );

  return std::move( lstHandlers );
}



