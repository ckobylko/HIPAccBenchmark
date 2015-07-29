#ifndef _IMAGE_ADD_DEFINES_H_
#define _IMAGE_ADD_DEFINES_H_

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/ImageAdd/ImageAdd.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define IMAGE_ADD_CHECK_OUTPUT( __PixelType ) \
  printf( "\n\n%6sChecking outputs ...\n", "" ); \
  spOutputImage->Fill( static_cast< OutputPixelType >( 0 ) ); \
  std::string strRefHandlerName; \
  for (auto itHandler : lstHandlers) { \
    if (itHandler == lstHandlers.front()) { \
      strRefHandlerName = itHandler->GetName(); \
      itHandler->Launch( spOutputImage, spInputImage1, spInputImage2 ); \
    } else { \
      CREATE_IMAGE( OutputImageType, spCompImage ); \
      itHandler->Launch( spCompImage, spInputImage1, spInputImage2 ); \
      printf( "\n%8s\"%10s\"  <-->  \"%10s\"  =  %5.3e", "", strRefHandlerName.c_str(), itHandler->GetName().c_str(), spOutputImage->MaxDeviation( *spCompImage ) ); \
    } \
  } \
  ImageIO::SaveImage( "Out_ImageAdd_" #__PixelType ".xsc", *spOutputImage ); \
  printf("\n");

#else

#define TEST_RUN_COUNT  100

#endif

#endif // _IMAGE_ADD_DEFINES_H_
