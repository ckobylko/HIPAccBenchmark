#ifndef _CONVOLUTION_FLOAT_HANDLERS_H_
#define _CONVOLUTION_FLOAT_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/ConvFloat/ConvFloatDefines.h"
#include "../ConvolutionHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class ConvolutionFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< ConvolutionFloatHandler, HandlerType >::value, "The handler type must be derived from ConvolutionFloatHandler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) = 0;
};

typedef std::shared_ptr< ConvolutionFloatHandler >  ConvolutionFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class ConvolutionFloatHandler_##__IS_Name final : public ConvolutionFloatHandler \
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
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccConvFloat_##__IS_Name##filterKernel, spOutputImage, spInputImage, ciStrideOutput, ciStrideInput, ciAnchor ); \
  }\
};



typedef std::list< ConvolutionFloatHandlerPtr >   HandlerList;

HandlerList ConvolutionFloat_GetScalarHandlers();

HandlerList ConvolutionFloat_GetSSEHandlers();

HandlerList ConvolutionFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _CONVOLUTION_FLOAT_HANDLERS_H_
