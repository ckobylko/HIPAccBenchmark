#include "NormalizedGradientFloatHandlers.h"

#include <immintrin.h>

namespace AVX {
#include "ccNormGradFloat_AVXfilter.cc"
}

class NormalizedGradientFloatHandler_AVXRef final : public NormalizedGradientFloatHandler
{
private:

  enum
  {
    VectorWidth = 32 / sizeof(OutputPixelType)
  };

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType  aaOutput1[ciHeight][ciWidth], OutputPixelType   aaOutput2[ciHeight][ciWidth],
             InputPixelType_1 aaInput1 [ciHeight][ciWidth], InputPixelType_2  aaInput2 [ciHeight][ciWidth] )
  {
    const __m256 cmmEpsilon = _mm256_set1_ps( static_cast< float >(1.0e-24) );

    for (int iY = 0; iY < ciHeight; ++iY)
    {
      _mm256_zeroall();

      OutputPixelType   *pOutput1 = aaOutput1[iY];
      OutputPixelType   *pOutput2 = aaOutput2[iY];
      InputPixelType_1  *pInput1  = aaInput1[iY];
      InputPixelType_2  *pInput2  = aaInput2[iY];

      for (int iX = 0; iX < ciWidth; iX += VectorWidth)
      {
        __m256 mmVal1 = _mm256_loadu_ps( pInput1 + iX );
        __m256 mmVal2 = _mm256_loadu_ps( pInput2 + iX );

        __m256 mmTemp     = _mm256_add_ps( _mm256_mul_ps(mmVal1, mmVal1), _mm256_mul_ps(mmVal2, mmVal2) );
        __m256 mmInvNorm  = _mm256_rsqrt_ps( _mm256_add_ps( mmTemp, cmmEpsilon ) );

        _mm256_storeu_ps( pOutput1 + iX, _mm256_mul_ps(mmVal1, mmInvNorm) );
        _mm256_storeu_ps( pOutput2 + iX, _mm256_mul_ps(mmVal2, mmInvNorm) );
      }

      _mm256_zeroupper();
    }
  }

public:

  virtual std::string GetName() const final override  { return "AVXRef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage1->Data, spOutputImage2->Data, spInputImage1->Data, spInputImage2->Data );
  }
};


MAKE_HANDLER(AVX);


HandlerList NormalizedGradientFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_AVXRef >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_AVX    >() );

  return std::move( lstHandlers );
}



