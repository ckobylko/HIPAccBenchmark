#pragma once


#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/BubbleSortOptUInt8/BubbleSortOptUInt8Defines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class BubbleSortMedianOptimizedUInt8Handler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< BubbleSortMedianOptimizedUInt8Handler, HandlerType >::value, "The handler type must be derived from BubbleSortMedianOptimizedUInt8Handler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) = 0;
};

typedef std::shared_ptr< BubbleSortMedianOptimizedUInt8Handler >  BubbleSortMedianOptimizedUInt8HandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class BubbleSortMedianOptimizedUInt8Handler_##__IS_Name final : public BubbleSortMedianOptimizedUInt8Handler \
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
    ##__IS_Name##::ccBubbleSortOptUInt8_##__IS_Name##filterKernel( spOutputImage->Data, spInputImage->Data, ciStrideInput, ciAnchor, ciAnchor, ciAnchor, ciStrideOutput, \
                                                                   OutputImageType::GetWidth() - ciAnchor * 2, OutputImageType::GetHeight() - ciAnchor * 2, \
                                                                   ciAnchor, ciAnchor ); \
  }\
};



typedef std::list< BubbleSortMedianOptimizedUInt8HandlerPtr >   HandlerList;

HandlerList BubbleSortMedianOptimizedUInt8_GetScalarHandlers();

HandlerList BubbleSortMedianOptimizedUInt8_GetSSEHandlers();

HandlerList BubbleSortMedianOptimizedUInt8_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}





