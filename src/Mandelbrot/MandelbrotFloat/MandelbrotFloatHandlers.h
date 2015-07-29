#ifndef _MANDELBROT_FLOAT_HANDLERS_H_
#define _MANDELBROT_FLOAT_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/MandelbrotFloat/MandelbrotFloatDefines.h"
#include "../MandelbrotHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class MandelbrotFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert(std::is_base_of< MandelbrotFloatHandler, HandlerType >::value, "The handler type must be derived from MandelbrotUInt8Handler!");

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) = 0;
};

typedef std::shared_ptr< MandelbrotFloatHandler >  MandelbrotFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class MandelbrotFloatHandler_##__IS_Name final : public MandelbrotFloatHandler \
{ \
public: \
  \
  virtual std::string GetName() const final override  { return #__IS_Name; } \
  \
  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) final override \
  {\
    const int ciStrideOutput = OutputImageType::GetWidth();\
    \
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccMandelbrotFloat_##__IS_Name##filterKernel, spOutputImage, ciStrideOutput, x0, y0, dx, dy, count ); \
  }\
};



typedef std::list< MandelbrotFloatHandlerPtr >   HandlerList;

HandlerList MandelbrotFloat_GetScalarHandlers();

HandlerList MandelbrotFloat_GetSSEHandlers();

HandlerList MandelbrotFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _MANDELBROT_FLOAT_HANDLERS_H_
