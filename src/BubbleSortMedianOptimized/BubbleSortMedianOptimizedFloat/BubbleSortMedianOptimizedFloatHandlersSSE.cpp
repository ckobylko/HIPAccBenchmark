#include "stdafx.h"
#include "BubbleSortMedianOptimizedFloatHandlers.h"

namespace SSE2    {
#include "ccBubbleSortOptFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccBubbleSortOptFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccBubbleSortOptFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccBubbleSortOptFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccBubbleSortOptFloat_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList BubbleSortMedianOptimizedFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_SSE2   >() );
  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_SSE3   >() );
  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_SSSE3  >() );
  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

