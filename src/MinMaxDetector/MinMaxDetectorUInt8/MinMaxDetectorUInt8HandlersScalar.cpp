#include "stdafx.h"
#include "MinMaxDetectorUInt8Handlers.h"

namespace Scalar  {
#include "ccMinMaxUInt8_Scalarfilter.cc"
}

#ifndef IGNORE_ARRAY_EXPORT
namespace Array   {
#include "ccMinMaxUInt8_Arrayfilter.cc"
}
#endif


class MinMaxDetectorUInt8Handler_ScalarRef final : public MinMaxDetectorUInt8Handler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType aaOutput[ciHeight][ciWidth], const InputPixelType_1 aaInput[ciHeight][ciWidth], const int ciAnchor )
  {
    for (int iRow = ciAnchor; iRow < ciHeight - ciAnchor; ++iRow)
    {
      for (int iCol = ciAnchor; iCol < ciWidth - ciAnchor; ++iCol)
      {
        const InputPixelType_1 TRefVal = aaInput[ iRow ][ iCol ];
        bool  bMaximum = true, bMinimum = true;

        for (int iY = -ciAnchor; iY <= ciAnchor; ++iY)
        {
          bool bBreak = false;

          for (int iX = -ciAnchor; iX <= ciAnchor; ++iX)
          {
            // Skip reference pixel
            if ((iY == 0) && (iX == 0))     continue;

            InputPixelType_1 TCurVal = aaInput[ iRow + iY ][ iCol + iX ];
            if (TCurVal > TRefVal)
            {
              bMaximum = false;
              bBreak   = (! bMinimum);
            }
            else if (TCurVal < TRefVal)
            {
              bMinimum = false;
              bBreak   = (! bMaximum);
            }

            if (bBreak)  break;
          }

          if (bBreak)  break;
        }

        OutputPixelType TOutVal = 0;
        if (bMaximum)   TOutVal += 128;
        if (bMinimum)   TOutVal += 64;

        aaOutput[ iRow ][ iCol ] = TOutVal;
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

class MinMaxDetectorUInt8Handler_Scalar final : public MinMaxDetectorUInt8Handler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccMinMaxUInt8_ScalarfilterKernel, spOutputImage, spInputImage, ciStrideOutput, ciAnchor );
  }
};


#ifndef IGNORE_ARRAY_EXPORT
MAKE_HANDLER(Array);
#endif



HandlerList MinMaxDetectorUInt8_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MinMaxDetectorUInt8Handler::Create< MinMaxDetectorUInt8Handler_ScalarRef >() );
  lstHandlers.push_back( MinMaxDetectorUInt8Handler::Create< MinMaxDetectorUInt8Handler_Scalar    >() );

#ifndef IGNORE_ARRAY_EXPORT
  lstHandlers.push_back( MinMaxDetectorUInt8Handler::Create< MinMaxDetectorUInt8Handler_Array     >() );
#endif

  return std::move( lstHandlers );
}


