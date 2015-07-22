#include "MandelbrotUInt8Handlers.h"

namespace AVX {
#include "ccMandelbrotUInt8_AVXfilter.cc"
}

#include "MandelbrotUInt8AVX.h"

MAKE_HANDLER(AVX);


class MandelbrotUInt8Handler_AVX_ISPC final : public MandelbrotUInt8Handler
{
public:

  virtual std::string GetName() const final override  { return "AVX (ISPC)"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    ispc::MandelbrotUInt8AVX(&spOutputImage->Data[0][0], OutputImageType::GetWidth(), OutputImageType::GetHeight(), ciStrideOutput, x0, y0, dx, dy, count);
  }
};



HandlerList MandelbrotUInt8_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_AVX      >() );
  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_AVX_ISPC >() );

  return std::move( lstHandlers );
}



