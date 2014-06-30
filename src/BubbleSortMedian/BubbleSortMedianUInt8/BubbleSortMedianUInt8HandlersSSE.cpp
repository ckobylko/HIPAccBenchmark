#include "stdafx.h"
#include "BubbleSortMedianUInt8Handlers.h"

namespace SSE2    {
#include "ccBubbleSortUInt8_SSE2filter.cc"
}
namespace SSE3    {
#include "ccBubbleSortUInt8_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccBubbleSortUInt8_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccBubbleSortUInt8_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccBubbleSortUInt8_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList BubbleSortMedianUInt8_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_SSE2   >() );
  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_SSE3   >() );
  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_SSSE3  >() );
  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_SSE4_1 >() );
  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_SSE4_2 >() );

  return std::move( lstHandlers );
}

