#include "stdafx.h"
#include "MinMaxDetectorFloatHandlers.h"

namespace SSE2    {
#include "ccMinMaxFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccMinMaxFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccMinMaxFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccMinMaxFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccMinMaxFloat_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList MinMaxDetectorFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_SSE2   >() );
  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_SSE3   >() );
  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_SSSE3  >() );
  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

