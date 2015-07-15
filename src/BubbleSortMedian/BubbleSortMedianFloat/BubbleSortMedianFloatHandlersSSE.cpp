#include "BubbleSortMedianFloatHandlers.h"

namespace SSE2    {
#include "ccBubbleSortFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccBubbleSortFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccBubbleSortFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccBubbleSortFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccBubbleSortFloat_SSE4_2filter.cc"
}


MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList BubbleSortMedianFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_SSE2   >() );
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_SSE3   >() );
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_SSSE3  >() );
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

