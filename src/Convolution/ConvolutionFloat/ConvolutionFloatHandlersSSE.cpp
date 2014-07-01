#include "stdafx.h"
#include "ConvolutionFloatHandlers.h"

namespace SSE2    {
#include "ccConvFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccConvFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccConvFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccConvFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccConvFloat_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList ConvolutionFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_SSE2   >() );
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_SSE3   >() );
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_SSSE3  >() );
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

