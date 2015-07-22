#include "MandelbrotUInt8Handlers.h"

namespace SSE4_2  {
#include "ccMandelbrotUInt8_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE4_2);


HandlerList MandelbrotUInt8_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_SSE4_2 >() );

  return std::move( lstHandlers );
}

