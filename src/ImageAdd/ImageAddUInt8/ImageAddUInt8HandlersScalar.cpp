#include "ImageAddUInt8Handlers.h"

namespace Scalar  {
#include "ccAddUInt8_Scalarfilter.cc"
}


class ImageAddUInt8Handler_ScalarRef final : public ImageAddUInt8Handler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run(OutputPixelType aaOutput[ciHeight][ciWidth], InputPixelType_1 aaInput1[ciHeight][ciWidth], InputPixelType_2 aaInput2[ciHeight][ciWidth])
  {
    for (int iY = 0; iY < ciHeight; ++iY)
    {
      for (int iX = 0; iX < ciWidth; ++iX)
      {
        aaOutput[iY][iX] = aaInput1[iY][iX] + aaInput2[iY][iX];
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "ScalarRef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, spInputImage1->Data, spInputImage2->Data );
  }
};

class ImageAddUInt8Handler_Scalar final : public ImageAddUInt8Handler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccAddUInt8_ScalarfilterKernel, spOutputImage, spInputImage1, spInputImage2, ciStrideOutput );
  }
};


HandlerList ImageAddUInt8_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddUInt8Handler::Create< ImageAddUInt8Handler_ScalarRef >() );
  lstHandlers.push_back( ImageAddUInt8Handler::Create< ImageAddUInt8Handler_Scalar    >() );

  return std::move( lstHandlers );
}


