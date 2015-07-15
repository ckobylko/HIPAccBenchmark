#include "NormalizedGradientFloatHandlers.h"
#include <cmath>

namespace Scalar  {
#include "ccNormGradFloat_Scalarfilter.cc"
}


class NormalizedGradientFloatHandler_ScalarRef final : public NormalizedGradientFloatHandler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run(OutputPixelType aaOutput1[ciHeight][ciWidth], OutputPixelType aaOutput2[ciHeight][ciWidth], InputPixelType_1 aaInput1[ciHeight][ciWidth], InputPixelType_2 aaInput2[ciHeight][ciWidth])
  {
    for (int iY = 0; iY < ciHeight; ++iY)
    {
      for (int iX = 0; iX < ciWidth; ++iX)
      {
        float fVal1 = static_cast< float >( aaInput1[ iY ][ iX ] );
        float fVal2 = static_cast< float >( aaInput2[ iY ][ iX ] );

        float fNorm = std::sqrt(fVal1 * fVal1 + fVal2 * fVal2) + static_cast<float>(1.0e-12);

        aaOutput1[ iY ][ iX ] = static_cast< OutputPixelType >( fVal1 / fNorm );
        aaOutput2[ iY ][ iX ] = static_cast< OutputPixelType >( fVal2 / fNorm );
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "ScalarRef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage1->Data, spOutputImage2->Data, spInputImage1->Data, spInputImage2->Data );
  }
};

class NormalizedGradientFloatHandler_Scalar final : public NormalizedGradientFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch(OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccNormGradFloat_ScalarfilterKernel, spOutputImage1, spOutputImage2, spInputImage1, spInputImage2, ciStrideOutput );
  }
};


HandlerList NormalizedGradientFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_ScalarRef >() );
  lstHandlers.push_back( NormalizedGradientFloatHandler::Create< NormalizedGradientFloatHandler_Scalar    >() );

  return std::move( lstHandlers );
}


