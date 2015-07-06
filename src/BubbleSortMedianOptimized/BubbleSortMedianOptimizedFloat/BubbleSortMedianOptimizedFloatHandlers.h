#pragma once


#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/BubbleSortOptFloat/BubbleSortOptFloatDefines.h"
#include "../BubbleSortMedianOptimizedHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class BubbleSortMedianOptimizedFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< BubbleSortMedianOptimizedFloatHandler, HandlerType >::value, "The handler type must be derived from BubbleSortMedianOptimizedFloatHandler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) = 0;
};

typedef std::shared_ptr< BubbleSortMedianOptimizedFloatHandler >  BubbleSortMedianOptimizedFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class BubbleSortMedianOptimizedFloatHandler_##__IS_Name final : public BubbleSortMedianOptimizedFloatHandler \
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
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccBubbleSortOptFloat_##__IS_Name##filterKernel, spOutputImage, spInputImage, ciStrideOutput, ciStrideInput, ciAnchor ); \
  }\
};



typedef std::list< BubbleSortMedianOptimizedFloatHandlerPtr >   HandlerList;

HandlerList BubbleSortMedianOptimizedFloat_GetScalarHandlers();

HandlerList BubbleSortMedianOptimizedFloat_GetSSEHandlers();

HandlerList BubbleSortMedianOptimizedFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}





