#include "stdafx.h"
#include "ImageAddIntHandlers.h"

#include <immintrin.h>

namespace AVX {
#include "ccAddInt_AVXfilter.cc"
}

class ImageAddIntHandler_AVXRef final : public ImageAddIntHandler
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
        __m256i mmIn1 = _mm256_lddqu_si256( reinterpret_cast<const __m256i *>( pInput1 + iX ) );
        __m256i mmIn2 = _mm256_lddqu_si256( reinterpret_cast<const __m256i *>( pInput2 + iX ) );

        __m128i mmResLo = _mm_add_epi32( _mm256_extractf128_si256(mmIn1, 0), _mm256_extractf128_si256(mmIn2, 0) );
        __m128i mmResHi = _mm_add_epi32( _mm256_extractf128_si256(mmIn1, 1), _mm256_extractf128_si256(mmIn2, 1) );

        _mm256_storeu_si256( reinterpret_cast<__m256i *>( pOutput + iX ), _mm256_set_m128i( mmResHi, mmResLo ) );
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


HandlerList ImageAddInt_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_AVXRef >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_AVX    >() );

  return std::move( lstHandlers );
}



