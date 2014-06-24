#include "stdafx.h"
#include "ImageAddFloatHandlers.h"

#include <xmmintrin.h>

namespace SSE     {
#include "ccAddFloat_SSEfilter.cc"
}
namespace SSE2    {
#include "ccAddFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccAddFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccAddFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccAddFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccAddFloat_SSE4_2filter.cc"
}

class ImageAddFloatHandler_SSERef final : public ImageAddFloatHandler
{
private:

  enum
  {
    VectorWidth = 16 / sizeof(OutputPixelType)
  };

  template <const int ciWidth, const int ciHeight>
  void _Run(OutputPixelType aaOutput[ciHeight][ciWidth], InputPixelType_1 aaInput1[ciHeight][ciWidth], InputPixelType_2 aaInput2[ciHeight][ciWidth])
  {
    for (int iY = 0; iY < ciHeight; ++iY)
    {
      OutputPixelType   *pOutput = aaOutput[iY];
      InputPixelType_1  *pInput1 = aaInput1[iY];
      InputPixelType_2  *pInput2 = aaInput2[iY];

      for (int iX = 0; iX < ciWidth; iX += VectorWidth)
      {
        __m128 mmIn1 = _mm_loadu_ps( pInput1 + iX );
        __m128 mmIn2 = _mm_loadu_ps( pInput2 + iX );

        _mm_storeu_ps( pOutput + iX, _mm_add_ps(mmIn1, mmIn2) );
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "SSERef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, spInputImage1->Data, spInputImage2->Data );
  }
};



MAKE_HANDLER(SSE);
MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList ImageAddFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSERef >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSE    >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSE2   >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSE3   >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSSE3  >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

