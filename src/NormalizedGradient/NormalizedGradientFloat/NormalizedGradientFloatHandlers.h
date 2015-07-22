#ifndef _NORMALIZED_GRADIENT_FLOAT_HANDLERS_H_
#define _NORMALIZED_GRADIENT_FLOAT_HANDLERS_H_

#include "../../../include/Benchmark/Image.h"
#include "../HIPAccSources/NormGradFloat/NormGradFloatDefines.h"
#include "../NormalizedGradientHandlerDefines.h"
#include <list>
#include <memory>
#include <string>
#include <type_traits>


MAKE_IMAGE_TYPE( InputImageType1, InputPixelType_1, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( InputImageType2, InputPixelType_2, ciImageWidth, ciImageHeight );
MAKE_IMAGE_TYPE( OutputImageType, OutputPixelType,  ciImageWidth, ciImageHeight );


class NormalizedGradientFloatHandler
{
public:

  template < class HandlerType >
  inline static std::shared_ptr< HandlerType > Create()
  {
    static_assert( std::is_base_of< NormalizedGradientFloatHandler, HandlerType >::value, "The handler type must be derived from NormalizedGradientFloatHandler!");

    return std::make_shared< HandlerType >();
  }


  virtual std::string GetName() const = 0;

  virtual void Launch( OutputImageTypePtr spOutputImage1, OutputImageTypePtr spOutputImage2, InputImageType1Ptr spInputImage1, InputImageType2Ptr spInputImage2 ) = 0;
};

typedef std::shared_ptr< NormalizedGradientFloatHandler >   NormalizedGradientFloatHandlerPtr;


#define MAKE_HANDLER( __IS_Name) \
class NormalizedGradientFloatHandler_##__IS_Name final : public NormalizedGradientFloatHandler \
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
    LAUNCH_HANDLER_VECTORIZED( ##__IS_Name##::ccNormGradFloat_##__IS_Name##filterKernel, spOutputImage1, spOutputImage2, spInputImage1, spInputImage2, ciStrideOutput, ciStrideInput1, ciStrideInput2 ); \
  }\
};



typedef std::list< NormalizedGradientFloatHandlerPtr >   HandlerList;

HandlerList NormalizedGradientFloat_GetScalarHandlers();

HandlerList NormalizedGradientFloat_GetSSEHandlers();

HandlerList NormalizedGradientFloat_GetAVXHandlers();


inline void AppendHandlerList(HandlerList &rDestinationList, const HandlerList &crSourceList)
{
  rDestinationList.insert( rDestinationList.end(), crSourceList.begin(), crSourceList.end() );
}


#endif // _NORMALIZED_GRADIENT_FLOAT_HANDLERS_H_
