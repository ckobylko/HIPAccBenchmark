#ifndef _TOPOLOGICAL_EROSION_DEFINES_H_
#define _TOPOLOGICAL_EROSION_DEFINES_H_

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/TopologicalErosion/TopologicalErosion.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define TOPOLOGICAL_EROSION_CHECK_OUTPUT( __PixelType ) \
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
  ImageIO::SaveImage( "Out_TopologicalErosion_" #__PixelType ".xsc", *spOutputImage ); \
  printf("\n");

#else

#define TEST_RUN_COUNT  100

#endif

#endif // _TOPOLOGICAL_EROSION_DEFINES_H_
