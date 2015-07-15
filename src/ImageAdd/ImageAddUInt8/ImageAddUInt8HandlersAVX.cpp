#include "ImageAddUInt8Handlers.h"


namespace AVX {
#include "ccAddUInt8_AVXfilter.cc"
}


MAKE_HANDLER(AVX);


HandlerList ImageAddUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddUInt8Handler::Create< ImageAddUInt8Handler_AVX    >() );

  return std::move( lstHandlers );
}



