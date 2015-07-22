#ifndef _BUBBLE_SORT_MEDIAN_UINT8_HANDLERS_H_
#define _BUBBLE_SORT_MEDIAN_UINT8_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/BubbleSortUInt8/BubbleSortUInt8Defines.h"
#include "../BubbleSortMedianHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType,  InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class BubbleSortMedianUInt8Handler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< BubbleSortMedianUInt8Handler, HandlerType >::value, "The handler type must be derived from BubbleSortMedianUInt8Handler!" );

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage, InputImageTypePtr spInputImage, unsigned int uiKernelSize ) = 0;
};

typedef std::shared_ptr< BubbleSortMedianUInt8Handler >  BubbleSortMedianUInt8HandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class BubbleSortMedianUInt8Handler_##__IS_Name final : public BubbleSortMedianUInt8Handler \
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
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccBubbleSortUInt8_##__IS_Name##filterKernel, spOutputImage, spInputImage, ciStrideOutput, ciStrideInput, ciAnchor ); \
  }\
};



typedef std::list< BubbleSortMedianUInt8HandlerPtr >   HandlerList;

HandlerList BubbleSortMedianUInt8_GetScalarHandlers();

HandlerList BubbleSortMedianUInt8_GetSSEHandlers();

HandlerList BubbleSortMedianUInt8_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _BUBBLE_SORT_MEDIAN_UINT8_HANDLERS_H_
