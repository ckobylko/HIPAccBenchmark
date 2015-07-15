#include "BubbleSortMedianUInt8Handlers.h"

namespace AVX {
#include "ccBubbleSortUInt8_AVXfilter.cc"
}

MAKE_HANDLER(AVX);


HandlerList BubbleSortMedianUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianUInt8Handler::Create< BubbleSortMedianUInt8Handler_AVX >() );

  return std::move( lstHandlers );
}



