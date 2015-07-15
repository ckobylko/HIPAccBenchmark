#include "NormalizedGradientFloatHandlers.h"

#include <xmmintrin.h>

namespace SSE     {
#include "ccNormGradFloat_SSEfilter.cc"
}
namespace SSE2    {
#include "ccNormGradFloat_SSE2filter.cc"
}
namespace SSE3    {
#include "ccNormGradFloat_SSE3filter.cc"
}
namespace SSSE3   {
#include "ccNormGradFloat_SSSE3filter.cc"
}
namespace SSE4_1  {
#include "ccNormGradFloat_SSE4_1filter.cc"
}
namespace SSE4_2  {
#include "ccNormGradFloat_SSE4_2filter.cc"
}

class NormalizedGradientFloatHandler_SSERef final : public NormalizedGradientFloatHandler
{
private:

  enum
  {
    VectorWidth = 16 / sizeof(OutputPixelType)
  };

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType  aaOutput1[ciHeight][ciWidth], OutputPixelType   aaOutput2[ciHeight][ciWidth],
             InputPixelType_1 aaInput1 [ciHeight][ciWidth], InputPixelType_2  aaInput2 [ciHeight][ciWidth] )
  {
    const __m128 cmmEpsilon = _mm_set1_ps( static_cast< float >(1.0e-24) );

    for (int iY = 0; iY < ciHeight; ++iY)
    {
      OutputPixelType   *pOutput1 = aaOutput1[iY];
      OutputPixelType   *pOutput2 = aaOutput2[iY];
      InputPixelType_1  *pInput1  = aaInput1[iY];
      InputPixelType_2  *pInput2  = aaInput2[iY];

      for (int iX = 0; iX < ciWidth; iX += VectorWidth)
      {
        __m128 mmVal1 = _mm_loadu_ps( pInput1 + iX );
        __m128 mmVal2 = _mm_loadu_ps( pInput2 + iX );

        __m128 mmTemp     = _mm_add_ps( _mm_mul_ps(mmVal1, mmVal1), _mm_mul_ps(mmVal2, mmVal2) );
        __m128 mmInvNorm  = _mm_rsqrt_ps( _mm_add_ps( mmTemp, cmmEpsilon ) );

        _mm_storeu_ps( pOutput1 + iX, _mm_mul_ps(mmVal1, mmInvNorm) );
        _mm_storeu_ps( pOutput2 + iX, _mm_mul_ps(mmVal2, mmInvNorm) );
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "SSERef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage1->Data, spOutputImage2->Data, spInputImage1->Data, spInputImage2->Data );
  }
};



MAKE_HANDLER(SSE);
MAKE_HANDLER(SSE2);
MAKE_HANDLER(SSE3);
MAKE_HANDLER(SSSE3);
MAKE_HANDLER(SSE4_1);
MAKE_HANDLER(SSE4_2);


HandlerList NormalizedGradientFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSERef >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSE    >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSE2   >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSE3   >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSSE3  >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSE4_1 >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_SSE4_2 >() );

  return std::move( lstHandlers );
}

