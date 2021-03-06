#ifndef _MIN_MAX_DETECTOR_FLOAT_HANDLERS_H_
#define _MIN_MAX_DETECTOR_FLOAT_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/MinMaxFloat/MinMaxFloatDefines.h"
#include "../MinMaxDetectorHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class MinMaxDetectorFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< MinMaxDetectorFloatHandler, HandlerType >::value, "The handler type must be derived from MinMaxDetectorFloatHandler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) = 0;
};

typedef std::shared_ptr< MinMaxDetectorFloatHandler >  MinMaxDetectorFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class MinMaxDetectorFloatHandler_##__IS_Name final : public MinMaxDetectorFloatHandler \
{ \
public: \
  \
  virtual std::string GetName() const final override  { return #__IS_Name; } \
  \
  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) final override \
  {\
    const int ciAnchor       = static_cast< int >( uiKernelSize >> 1 ); \
    const int ciStrideInput  = InputImageType::GetWidth();\
    const int ciStrideOutput = OutputImageType::GetWidth();\
    \
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccMinMaxFloat_##__IS_Name##filterKernel, spOutputImage, spInputImage, ciStrideOutput, ciStrideInput, ciAnchor ); \
  }\
};



typedef std::list< MinMaxDetectorFloatHandlerPtr >   HandlerList;

HandlerList MinMaxDetectorFloat_GetScalarHandlers();

HandlerList MinMaxDetectorFloat_GetSSEHandlers();

HandlerList MinMaxDetectorFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _MIN_MAX_DETECTOR_FLOAT_HANDLERS_H_
