#include "stdafx.h"
#include "BubbleSortMedianOptimizedFloatHandlers.h"
#include <algorithm>

namespace Scalar  {
#include "ccBubbleSortOptFloat_Scalarfilter.cc"
}


class BubbleSortMedianOptimizedFloatHandler_ScalarRef final : public BubbleSortMedianOptimizedFloatHandler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType aaOutput[ciHeight][ciWidth], const InputPixelType_1 aaInput[ciHeight][ciWidth], const int ciAnchor )
  {
    InputPixelType_1 aSortingBuffer[256];

    for (int iRow = ciAnchor; iRow < ciHeight - ciAnchor; ++iRow)
    {
      for (int iCol = ciAnchor; iCol < ciWidth - ciAnchor; ++iCol)
      {
        int iDataSize = 0;

        // Load the kernel into the sorting buffer
        for (int iY = -ciAnchor; iY <= ciAnchor; ++iY)
        {
          for (int iX = -ciAnchor; iX <= ciAnchor; ++iX)
          {
            aSortingBuffer[ iDataSize ] = aaInput[iRow + iY][iCol + iX];
            ++iDataSize;
          }
        }

        // Sort the buffer
        for (int iOuter = iDataSize; iOuter > 1; --iOuter)
        {
          InputPixelType_1 TRefVal = aSortingBuffer[0];

          for (int iInner = 1; iInner < iOuter; ++iInner)
          {
            InputPixelType_1 TCompVal   = aSortingBuffer[iInner];
            aSortingBuffer[iInner - 1]  = min( TRefVal, TCompVal );

            TRefVal                     = max( TRefVal, TCompVal );
            aSortingBuffer[iInner]      = TRefVal;
          }
        }

        // Write the output value
        aaOutput[ iRow ][ iCol ] = static_cast< OutputPixelType >( aSortingBuffer[ iDataSize >> 1 ] );\
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

class BubbleSortMedianOptimizedFloatHandler_Scalar final : public BubbleSortMedianOptimizedFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccBubbleSortOptFloat_ScalarfilterKernel, spOutputImage, spInputImage, ciStrideOutput, ciAnchor );
  }
};


HandlerList BubbleSortMedianOptimizedFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_ScalarRef >() );
  lstHandlers.push_back( BubbleSortMedianOptimizedFloatHandler::Create< BubbleSortMedianOptimizedFloatHandler_Scalar    >() );

  return std::move( lstHandlers );
}


