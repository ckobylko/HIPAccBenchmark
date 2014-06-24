#pragma once


#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/AddFloat/AddFloatDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType1, InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( InputImageType2, InputPixelType_2, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class ImageAddFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< ImageAddFloatHandler, HandlerType >::value, "The handler type must be derived from ImageAddFloatHandler!");

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2 ) = 0;
};

typedef std::shared_ptr< ImageAddFloatHandler >  ImageAddFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class ImageAddFloatHandler_##__IS_Name final : public ImageAddFloatHandler \
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
    ##__IS_Name##::ccAddFloat_##__IS_Name##filterKernel( spOutputImage->Data, spInputImage1->Data, ciStrideInput1, spInputImage2->Data, ciStrideInput2, ciStrideOutput, \
                                                         OutputImageType::GetWidth(), OutputImageType::GetHeight() ); \
  }\
};



typedef std::list< ImageAddFloatHandlerPtr >   HandlerList;

HandlerList ImageAddFloat_GetScalarHandlers();

HandlerList ImageAddFloat_GetSSEHandlers();

HandlerList ImageAddFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}





