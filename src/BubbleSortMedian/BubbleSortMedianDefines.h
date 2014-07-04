#pragma once

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/BubbleSortMedian/BubbleSortMedian.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define BUBBLE_SORT_MEDIAN_CHECK_OUTPUT( __PixelType ) \
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
  ImageIO::SaveImage( "Out_BubbleSortMedian_" #__PixelType ".xsc", *spOutputImage ); \
  printf("\n");

#endif


