#include "BubbleSortMedianFloatHandlers.h"

namespace AVX {
#include "ccBubbleSortFloat_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList BubbleSortMedianFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_AVX >() );

  return std::move( lstHandlers );
}



