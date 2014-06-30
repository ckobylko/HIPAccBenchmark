#include "stdafx.h"
#include "BubbleSortMedianFloatHandlers.h"
#include <algorithm>

namespace Scalar  {
#include "ccBubbleSortFloat_Scalarfilter.cc"
}

#ifndef IGNORE_ARRAY_EXPORT
namespace Array   {
#include "ccBubbleSortFloat_Arrayfilter.cc"
}
#endif


class BubbleSortMedianFloatHandler_ScalarRef final : public BubbleSortMedianFloatHandler
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
          for (int iInner = 1; iInner < iOuter; ++iInner)
          {
            if (aSortingBuffer[iInner - 1] > aSortingBuffer[iInner])
            {
              InputPixelType_1 TBuffer    = aSortingBuffer[iInner - 1];
              aSortingBuffer[iInner - 1]  = aSortingBuffer[iInner];
              aSortingBuffer[iInner]      = TBuffer;
            }
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

class BubbleSortMedianFloatHandler_Scalar final : public BubbleSortMedianFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();
  
    Scalar::ccBubbleSortFloat_ScalarfilterKernel( spOutputImage->Data, spInputImage->Data, ciAnchor, ciAnchor, ciAnchor, ciStrideOutput,
                                                  OutputImageType::GetWidth() - ciAnchor * 2, OutputImageType::GetHeight() - ciAnchor * 2,
                                                  ciAnchor, ciAnchor );
  }
};


#ifndef IGNORE_ARRAY_EXPORT
MAKE_HANDLER(Array);
#endif



HandlerList BubbleSortMedianFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_ScalarRef >() );
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_Scalar    >() );

#ifndef IGNORE_ARRAY_EXPORT
  lstHandlers.push_back( BubbleSortMedianFloatHandler::Create< BubbleSortMedianFloatHandler_Array     >() );
#endif

  return std::move( lstHandlers );
}


