#ifndef _MANDELBROT_UINT8_HANDLERS_H_
#define _MANDELBROT_UINT8_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/MandelbrotUInt8/MandelbrotUInt8Defines.h"
#include "../MandelbrotHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class MandelbrotUInt8Handler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< MandelbrotUInt8Handler, HandlerType >::value, "The handler type must be derived from MandelbrotUInt8Handler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) = 0;
};

typedef std::shared_ptr< MandelbrotUInt8Handler >  MandelbrotUInt8HandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class MandelbrotUInt8Handler_##__IS_Name final : public MandelbrotUInt8Handler \
{ \
public: \
  \
  virtual std::string GetName() const final override  { return #__IS_Name; } \
  \
  virtual void Launch( OutputImageTypePtr spOutputImage, float x0, float y0, float dx, float dy, int count ) final override \
  {\
    const int ciStrideOutput = OutputImageType::GetWidth();\
    \
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccMandelbrotUInt8_##__IS_Name##filterKernel, spOutputImage, ciStrideOutput, x0, y0, dx, dy, count ); \
  }\
};



typedef std::list< MandelbrotUInt8HandlerPtr >   HandlerList;

HandlerList MandelbrotUInt8_GetScalarHandlers();

HandlerList MandelbrotUInt8_GetSSEHandlers();

HandlerList MandelbrotUInt8_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _MANDELBROT_UINT8_HANDLERS_H_
