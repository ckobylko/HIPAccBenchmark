#include "stdafx.h"
#include "ConvolutionFloatHandlers.h"
#include <algorithm>

namespace Scalar  {
#include "ccConvFloat_Scalarfilter.cc"
}

#ifndef IGNORE_ARRAY_EXPORT
namespace Array   {
#include "ccConvFloat_Arrayfilter.cc"
}
#endif


class ConvolutionFloatHandler_ScalarRef final : public ConvolutionFloatHandler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType aaOutput[ciHeight][ciWidth], const InputPixelType_1 aaInput[ciHeight][ciWidth], const int ciAnchor )
  {
    const int   ciKernelSize  = (ciAnchor << 1) + 1;
    const float cfCoeff       = 1.f / static_cast< float >(ciKernelSize * ciKernelSize);

    for (int iRow = ciAnchor; iRow < ciHeight - ciAnchor; ++iRow)
    {
      for (int iCol = ciAnchor; iCol < ciWidth - ciAnchor; ++iCol)
      {
        float fAccumulator = 0.f;

        for (int iY = -ciAnchor; iY <= ciAnchor; ++iY)
        {
          for (int iX = -ciAnchor; iX <= ciAnchor; ++iX)
          {
            fAccumulator += static_cast< float >( aaInput[iRow + iY][iCol + iX] ) * cfCoeff;
          }
        }

        aaOutput[ iRow ][ iCol ] = static_cast< OutputPixelType >( fAccumulator );
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "ScalarRef"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, spInputImage->Data, static_cast< int >( uiKernelSize >> 1 ) );
  }
};

class ConvolutionFloatHandler_Scalar final : public ConvolutionFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccConvFloat_ScalarfilterKernel, spOutputImage, spInputImage, ciStrideOutput, ciAnchor );
  }
};


#ifndef IGNORE_ARRAY_EXPORT
MAKE_HANDLER(Array);
#endif



HandlerList ConvolutionFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_ScalarRef >() );
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler_Scalar    >() );

#ifndef IGNORE_ARRAY_EXPORT
  lstHandlers.push_back( ConvolutionFloatHandler::Create< ConvolutionFloatHandler     >() );
#endif

  return std::move( lstHandlers );
}


