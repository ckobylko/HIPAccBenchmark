#include "stdafx.h"
#include "TopologicalErosionUInt8Handlers.h"
#include <algorithm>

namespace Scalar  {
#include "ccTopErosionUInt8_Scalarfilter.cc"
}

#ifndef IGNORE_ARRAY_EXPORT
namespace Array   {
#include "ccTopErosionUInt8_Arrayfilter.cc"
}
#endif


class TopologicalErosionUInt8Handler_ScalarRef final : public TopologicalErosionUInt8Handler
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

class TopologicalErosionUInt8Handler_Scalar final : public TopologicalErosionUInt8Handler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();
  
    Scalar::ccTopErosionUInt8_ScalarfilterKernel( spOutputImage->Data, spInputImage->Data, ciAnchor, ciAnchor, ciAnchor, ciStrideOutput,
                                                  OutputImageType::GetWidth() - ciAnchor * 2, OutputImageType::GetHeight() - ciAnchor * 2,
                                                  ciAnchor, ciAnchor );
  }
};


#ifndef IGNORE_ARRAY_EXPORT
MAKE_HANDLER(Array);
#endif



HandlerList TopologicalErosionUInt8_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( TopologicalErosionUInt8Handler::Create< TopologicalErosionUInt8Handler_ScalarRef >() );
  lstHandlers.push_back( TopologicalErosionUInt8Handler::Create< TopologicalErosionUInt8Handler_Scalar    >() );

#ifndef IGNORE_ARRAY_EXPORT
  lstHandlers.push_back( TopologicalErosionUInt8Handler::Create< TopologicalErosionUInt8Handler_Array     >() );
#endif

  return std::move( lstHandlers );
}


