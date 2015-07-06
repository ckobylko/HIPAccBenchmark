#pragma once


#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/AddUInt8/AddUInt8Defines.h"
#include "../ImageAddHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType1, InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( InputImageType2, InputPixelType_2, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class ImageAddUInt8Handler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< ImageAddUInt8Handler, HandlerType >::value, "The handler type must be derived from ImageAddUInt8Handler!");

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2 ) = 0;
};

typedef std::shared_ptr< ImageAddUInt8Handler >  ImageAddUInt8HandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class ImageAddUInt8Handler_##__IS_Name final : public ImageAddUInt8Handler \
{ \
public: \
  \
  virtual std::string GetName() const final override  { return #__IS_Name; } \
  \
  virtual void Launch(OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override \
  {\
    const int ciStrideInput1 = InputImageType1::GetWidth();\
    const int ciStrideInput2 = InputImageType2::GetWidth();\
    const int ciStrideOutput = OutputImageType::GetWidth();\
    \
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccAddUInt8_##__IS_Name##filterKernel, spOutputImage, spInputImage1, spInputImage2, ciStrideOutput, ciStrideInput1, ciStrideInput2 ); \
  }\
};



typedef std::list< ImageAddUInt8HandlerPtr >   HandlerList;

HandlerList ImageAddUInt8_GetScalarHandlers();

HandlerList ImageAddUInt8_GetSSEHandlers();

HandlerList ImageAddUInt8_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}





