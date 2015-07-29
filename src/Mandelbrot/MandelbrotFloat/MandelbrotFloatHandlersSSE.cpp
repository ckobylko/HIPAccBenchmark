#include "MandelbrotFloatHandlers.h"

namespace SSE4_2  {
#include "ccMandelbrotFloat_SSE4_2filter.cc"
}

#include "MandelbrotFloatSSE4_2.h"

MAKE_HANDLER(SSE4_2);

class MandelbrotFloatHandler_SSE4_2_ISPC final : public MandelbrotFloatHandler
{
public:

  virtual std::string GetName() const final override  { return "SSE4_2 (ISPC)"; }

  virtual void Launch(OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count) final override
  {
    const int ciStrideOutput = OutputImageType::GetWidth();

    ispc::MandelbrotFloatSSE4_2(&spOutputImage->Data[0][0], OutputImageType::GetWidth(), OutputImageType::GetHeight(), ciStrideOutput, x0, y0, dx, dy, count);
  }
};


HandlerList MandelbrotFloat_GetSSEHandlers()
{
  HandlerList lstHandlers;

  lstHandlers.push_back( MandelbrotFloatHandler::Create< MandelbrotFloatHandler_SSE4_2      >() );
  lstHandlers.push_back( MandelbrotFloatHandler::Create< MandelbrotFloatHandler_SSE4_2_ISPC >() );

  return std::move( lstHandlers );
}

