#include "MandelbrotFloatHandlers.h"

namespace AVX {
#include "ccMandelbrotFloat_AVXfilter.cc"
}

#include "MandelbrotFloatAVX.h"

MAKE_HANDLER(AVX);


class MandelbrotFloatHandler_AVX_ISPC final : public MandelbrotFloatHandler
{
public:

  virtual std::string GetName() const final override  { return "AVX (ISPC)"; }

  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    ispc::MandelbrotFloatAVX(&spOutputImage->Data[0][0], OutputImageType::GetWidth(), OutputImageType::GetHeight(), ciStrideOutput, x0, y0, dx, dy, count);
  }
};



HandlerList MandelbrotFloat_GetAVXHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotFloatHandler::Create< MandelbrotFloatHandler_AVX      >() );
  lstHandlers.push_back( MandelbrotFloatHandler::Create< MandelbrotFloatHandler_AVX_ISPC >() );

  return std::move( lstHandlers );
}



