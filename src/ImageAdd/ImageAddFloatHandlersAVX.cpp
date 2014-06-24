#include "stdafx.h"
#include "ImageAddFloatHandlers.h"

#include <immintrin.h>

namespace AVX {
#include "ccAddFloat_AVXfilter.cc"
}

class ImageAddFloatHandler_AVXRef final : public ImageAddFloatHandler
{
private:

  enum
  {
    VectorWidth = 32 / sizeof(OutputPixelType)
  };

  template <const int ciWidth, const int ciHeight>
  void _Run(OutputPixelType aaOutput[ciHeight][ciWidth], InputPixelType_1 aaInput1[ciHeight][ciWidth], InputPixelType_2 aaInput2[ciHeight][ciWidth])
  {
    for (int iY = 0; iY < ciHeight; ++iY)
    {
      _mm256_zeroall();

      OutputPixelType   *pOutput = aaOutput[iY];
      InputPixelType_1  *pInput1 = aaInput1[iY];
      InputPixelType_2  *pInput2 = aaInput2[iY];

      for (int iX = 0; iX < ciWidth; iX += VectorWidth)
      {
        __m256 mmIn1 = _mm256_loadu_ps( pInput1 + iX );
        __m256 mmIn2 = _mm256_loadu_ps( pInput2 + iX );

        _mm256_storeu_ps( pOutput + iX, _mm256_add_ps(mmIn1, mmIn2) );
      }

      _mm256_zeroupper();
    }
  }

public:

  virtual std::string GetName() const final override  { return "AVXRef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, spInputImage1->Data, spInputImage2->Data );
  }
};


MAKE_HANDLER(AVX);


HandlerList ImageAddFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_AVXRef >() );
  lstHandlers.push_back( ImageAddFloatHandler::Create< ImageAddFloatHandler_AVX    >() );

  return std::move( lstHandlers );
}



