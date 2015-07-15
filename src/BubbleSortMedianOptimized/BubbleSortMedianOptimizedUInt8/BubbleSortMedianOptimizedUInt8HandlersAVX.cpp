#include "BubbleSortMedianOptimizedUInt8Handlers.h"

namespace AVX {
#include "ccBubbleSortOptUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList BubbleSortMedianOptimizedUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianOptimizedUInt8Handler::Create< BubbleSortMedianOptimizedUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



