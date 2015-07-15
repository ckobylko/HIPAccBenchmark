#include "TopologicalErosionFloatHandlers.h"
#include <algorithm>

namespace Scalar  {
#include "ccTopErosionFloat_Scalarfilter.cc"
}


class TopologicalErosionFloatHandler_ScalarRef final : public TopologicalErosionFloatHandler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType aaOutput[ciHeight][ciWidth], const InputPixelType_1 aaInput[ciHeight][ciWidth], const int ciAnchor )
  {
    for (int iRow = ciAnchor; iRow < ciHeight - ciAnchor; ++iRow)
    {
      for (int iCol = ciAnchor; iCol < ciWidth - ciAnchor; ++iCol)
      {
        InputPixelType_1 TOutVal = aaInput[ iRow ][ iCol ];

        for (int iY = -ciAnchor; iY <= ciAnchor; ++iY)
        {
          for (int iX = -ciAnchor; iX <= ciAnchor; ++iX)
          {
            TOutVal = min( TOutVal, aaInput[iRow + iY][iCol + iX] );
          }
        }

        aaOutput[ iRow ][ iCol ] = static_cast< OutputPixelType >( TOutVal );
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

class TopologicalErosionFloatHandler_Scalar final : public TopologicalErosionFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccTopErosionFloat_ScalarfilterKernel, spOutputImage, spInputImage, ciStrideOutput, ciAnchor );
  }
};


HandlerList TopologicalErosionFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( TopologicalErosionFloatHandler::Create< TopologicalErosionFloatHandler_ScalarRef >() );
  lstHandlers.push_back( TopologicalErosionFloatHandler::Create< TopologicalErosionFloatHandler_Scalar    >() );

  return std::move( lstHandlers );
}


