#ifndef _BUBBLE_SORT_MEDIAN_OPTIMIZED_DEFINES_H_
#define _BUBBLE_SORT_MEDIAN_OPTIMIZED_DEFINES_H_

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/BubbleSortMedianOptimized/BubbleSortMedianOptimized.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define BUBBLE_SORT_MEDIAN_OPTIMIZED_CHECK_OUTPUT( __PixelType ) \
  printf( "\n\n%6sChecking outputs ...\n", "" ); \
  spOutputImage->Fill( static_cast< OutputPixelType >( 0 ) ); \
  std::string strRefHandlerName; \
  for (auto itHandler : lstHandlers) { \
    if (itHandler == lstHandlers.front()) { \
      strRefHandlerName = itHandler->GetName(); \
      itHandler->Launch( spOutputImage, spInputImage, uiKernelSize ); \
    } else { \
      CREATE_IMAGE( OutputImageType, spCompImage ); \
      itHandler->Launch( spCompImage, spInputImage, uiKernelSize ); \
      printf( "\n%8s\"%10s\"  <-->  \"%10s\"  =  %5.3e", "", strRefHandlerName.c_str(), itHandler->GetName().c_str(), spOutputImage->MaxDeviation( *spCompImage ) ); \
    } \
  } \
  ImageIO::SaveImage( "Out_BubbleSortMedianOptimized_" #__PixelType ".xsc", *spOutputImage ); \
  printf("\n");

#endif

#endif // _BUBBLE_SORT_MEDIAN_OPTIMIZED_DEFINES_H_
