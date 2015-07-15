#include "MinMaxDetectorFloatHandlers.h"

namespace Scalar  {
#include "ccMinMaxFloat_Scalarfilter.cc"
}


class MinMaxDetectorFloatHandler_ScalarRef final : public MinMaxDetectorFloatHandler
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

class MinMaxDetectorFloatHandler_Scalar final : public MinMaxDetectorFloatHandler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override
  {
    const int ciAnchor        = static_cast< int >( uiKernelSize >> 1 );
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccMinMaxFloat_ScalarfilterKernel, spOutputImage, spInputImage, ciStrideOutput, ciAnchor );
  }
};


HandlerList MinMaxDetectorFloat_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_ScalarRef >() );
  lstHandlers.push_back( MinMaxDetectorFloatHandler::Create< MinMaxDetectorFloatHandler_Scalar    >() );

  return std::move( lstHandlers );
}


