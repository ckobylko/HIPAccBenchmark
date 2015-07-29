#ifndef _NORMALIZED_GRADIENT_DEFINES_H_
#define _NORMALIZED_GRADIENT_DEFINES_H_

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/NormalizedGradient/NormalizedGradient.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define NORMALIZED_GRADIENT_CHECK_OUTPUT( __PixelType ) \
  printf( "\n\n%6sChecking outputs ...\n", "" ); \
  spOutputImage1->Fill( static_cast< OutputPixelType >( 0 ) ); \
  spOutputImage2->Fill( static_cast< OutputPixelType >( 0 ) ); \
  std::string strRefHandlerName; \
  for (auto itHandler : lstHandlers) { \
    if (itHandler == lstHandlers.front()) { \
      strRefHandlerName = itHandler->GetName(); \
      itHandler->Launch( spOutputImage1, spOutputImage2, spInputImage1, spInputImage2 ); \
    } else { \
      CREATE_IMAGE( OutputImageType, spCompImage1 ); \
      CREATE_IMAGE( OutputImageType, spCompImage2 ); \
      itHandler->Launch( spCompImage1, spCompImage2, spInputImage1, spInputImage2 ); \
      double dMaxDev = std::max( spOutputImage1->MaxDeviation( *spCompImage1 ), spOutputImage2->MaxDeviation( *spCompImage2 ) ); \
      printf( "\n%8s\"%10s\"  <-->  \"%10s\"  =  %5.3e", "", strRefHandlerName.c_str(), itHandler->GetName().c_str(), dMaxDev ); \
    } \
  } \
  /* Scale output images */ \
  const float cfScaleFactor = 512.f; \
  for (int iY = 0; iY < OutputImageType::GetHeight(); ++iY) { \
    for (int iX = 0; iX < OutputImageType::GetWidth(); ++iX) { \
      spOutputImage1->Data[ iY ][ iX ] = ( spOutputImage1->Data[ iY ][ iX ] + 1.0f ) * cfScaleFactor; \
      spOutputImage2->Data[ iY ][ iX ] = ( spOutputImage2->Data[ iY ][ iX ] + 1.0f ) * cfScaleFactor; \
    } \
  } \
  ImageIO::SaveImage( "Out_NormalizedGradient_" #__PixelType "_Cos.xsc", *spOutputImage1 ); \
  ImageIO::SaveImage( "Out_NormalizedGradient_" #__PixelType "_Sin.xsc", *spOutputImage2 ); \
  printf("\n");

#else

#define TEST_RUN_COUNT  100

#endif

#endif // _NORMALIZED_GRADIENT_DEFINES_H_
