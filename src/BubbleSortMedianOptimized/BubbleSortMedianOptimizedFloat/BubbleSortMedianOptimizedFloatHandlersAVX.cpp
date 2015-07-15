#include "BubbleSortMedianOptimizedFloatHandlers.h"

namespace AVX {
#include "ccBubbleSortOptFloat_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList BubbleSortMedianOptimizedFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_AVX >() );

  return std::move( lstHandlers );
}



