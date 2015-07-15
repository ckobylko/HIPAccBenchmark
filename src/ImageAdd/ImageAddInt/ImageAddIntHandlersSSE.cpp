#include "ImageAddIntHandlers.h"

#include <emmintrin.h>

namespace SSE2    {
#include "ccAddInt_SSE2filter.cc"
}
namespace SSE3    {
#include "ccAddInt_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccAddInt_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccAddInt_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccAddInt_SSE4_2filter.cc"
}

class ImageAddIntHandler_SSE2Ref final : public ImageAddIntHandler
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
        __m128i mmIn1 = _mm_loadu_si128( reinterpret_cast<const __m128i *>( pInput1 + iX ) );
        __m128i mmIn2 = _mm_loadu_si128( reinterpret_cast<const __m128i *>( pInput2 + iX ) );

        _mm_storeu_si128( reinterpret_cast<__m128i *>( pOutput + iX ), _mm_add_epi32(mmIn1, mmIn2) );
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "SSE2Ref"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, spInputImage1->Data, spInputImage2->Data );
  }
};



MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList ImageAddInt_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSE2Ref >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSE2   >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSE3   >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSSE3  >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSE4_1 >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

