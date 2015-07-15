#include "NormalizedGradientUInt8Handlers.h"


namespace AVX {
#include "ccNormGradUInt8_AVXfilter.cc"
}


MAKE_HANDLER(AVX);


HandlerList NormalizedGradientUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( NormalizedGradientUInt8Handler::Create< NormalizedGradientUInt8Handler_AVX    >() );

  return std::move( lstHandlers );
}



