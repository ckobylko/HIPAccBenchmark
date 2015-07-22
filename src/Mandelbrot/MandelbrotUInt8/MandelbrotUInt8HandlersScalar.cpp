#include "MandelbrotUInt8Handlers.h"

namespace Scalar  {
#include "ccMandelbrotUInt8_Scalarfilter.cc"
}


class MandelbrotUInt8Handler_ScalarRef final : public MandelbrotUInt8Handler
{
private:

  template <const int ciWidth, const int ciHeight>
  void _Run( OutputPixelType aaOutput[ciHeight][ciWidth], float x0, float y0, float dx, float dy, int count )
  {
    for (int iRow = 0; iRow < ciHeight - 0; ++iRow)
    {
      for (int iCol = 0; iCol < ciWidth - 0; ++iCol)
      {
        OutputPixelType TOutVal = 0;
        float c_re = iCol * dx + x0;
        float c_im = iRow * dy + y0;

        float z_re = c_re, z_im = c_im;
        for (int i = 0; i < count; ++i)
        {
          if (z_re * z_re + z_im * z_im > 4.)
          {
            TOutVal = static_cast< OutputPixelType >(i);
            break;
          }
          float new_re = z_re*z_re - z_im*z_im;
          float new_im = 2.f * z_re * z_im;
          z_re = c_re + new_re;
          z_im = c_im + new_im;
        }

        aaOutput[ iRow ][ iCol ] = TOutVal;
      }
    }
  }

public:

  virtual std::string GetName() const final override  { return "ScalarRef"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count) final override
  {
    _Run< OutputImageType::Width, OutputImageType::Height >( spOutputImage->Data, x0, y0, dx, dy, count );
  }
};

class MandelbrotUInt8Handler_Scalar final : public MandelbrotUInt8Handler
{
public:
  
  virtual std::string GetName() const final override  { return "Scalar"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) final override
  {
    const int ciStrideOutput  = OutputImageType::GetWidth();

    LAUNCH_HANDLER_SCALAR( Scalar::ccMandelbrotUInt8_ScalarfilterKernel, spOutputImage, ciStrideOutput, x0, y0, dx, dy, count );
  }
};


HandlerList MandelbrotUInt8_GetScalarHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_ScalarRef >() );
  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_Scalar    >() );

  return std::move( lstHandlers );
}


