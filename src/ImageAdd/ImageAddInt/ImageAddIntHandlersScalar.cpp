#include "stdafx.h"
#include "ImageAddIntHandlers.h"

namespace Scalar  {
#include "ccAddInt_Scalarfilter.cc"
}


class ImageAddIntHandler_ScalarRef final : public ImageAddIntHandler
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

class ImageAddIntHandler_Scalar final : public ImageAddIntHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccAddInt_ScalarfilterKernel, spOutputImage, spInputImage1, spInputImage2, ciStrideOutput );
  }
};


HandlerList ImageAddInt_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_ScalarRef >() );
  lstHandlers.push_back( ImageAddIntHandler::Create< ImageAddIntHandler_Scalar    >() );

  return std::move( lstHandlers );
}


