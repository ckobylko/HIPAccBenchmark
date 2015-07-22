#include "MandelbrotUInt8Handlers.h"

namespace SSE4_2  {
#include "ccMandelbrotUInt8_SSE4_2filter.cc"
}

#include "MandelbrotUInt8SSE4_2.h"

MAKE_HANDLER(SSE4_2);

class MandelbrotUInt8Handler_SSE4_2_ISPC final : public MandelbrotUInt8Handler
{
public:

  virtual std::string GetName() const final override  { return "SSE4_2 (ISPC)"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    ispc::MandelbrotUInt8SSE4_2(&spOutputImage->Data[0][0], OutputImageType::GetWidth(), OutputImageType::GetHeight(), ciStrideOutput, x0, y0, dx, dy, count);
  }
};


HandlerList MandelbrotUInt8_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_SSE4_2      >() );
  lstHandlers.push_back( MandelbrotUInt8Handler::Create< MandelbrotUInt8Handler_SSE4_2_ISPC >() );

  return std::move( lstHandlers );
}

