#pragma once


#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/NormGradUInt8/NormGradUInt8Defines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType1, InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( InputImageType2, InputPixelType_2, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class NormalizedGradientUInt8Handler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< NormalizedGradientUInt8Handler, HandlerType >::value, "The handler type must be derived from NormalizedGradientUInt8Handler!");

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2 ) = 0;
};

typedef std::shared_ptr< NormalizedGradientUInt8Handler >   NormalizedGradientUInt8HandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class NormalizedGradientUInt8Handler_##__IS_Name final : public NormalizedGradientUInt8Handler \
{ \
public: \
  \
  virtual std::string GetName() const final override  { return #__IS_Name; } \
  \
  virtual void Launch(OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2) final override \
  {\
    const int ciStrideInput1 = InputImageType1::GetWidth();\
    const int ciStrideInput2 = InputImageType2::GetWidth();\
    const int ciStrideOutput = OutputImageType::GetWidth();\
    \
    ##__IS_Name##::ccNormGradUInt8_##__IS_Name##filterKernel( spOutputImage1->Data, spOutputImage2->Data, spInputImage1->Data,  ciStrideInput1, \
                                                              spInputImage2->Data,  ciStrideInput2,       ciStrideOutput,       OutputImageType::GetWidth(), \
                                                              OutputImageType::GetHeight() ); \
}\
};



typedef std::list< NormalizedGradientUInt8HandlerPtr >   HandlerList;

HandlerList NormalizedGradientUInt8_GetScalarHandlers();

HandlerList NormalizedGradientUInt8_GetSSEHandlers();

HandlerList NormalizedGradientUInt8_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}





