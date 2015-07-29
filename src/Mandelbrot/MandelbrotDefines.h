#ifndef _MANDELBROT_DEFINES_H_
#define _MANDELBROT_DEFINES_H_

#include "../../include/Benchmark/CommonDefines.h"
#include "../../include/Benchmark/ImageIO.h"
#include "../../include/Mandelbrot/Mandelbrot.h"
#include <omp.h>


#ifdef CONFIG_CHECK_OUTPUT

#define MANDELBROT_CHECK_OUTPUT( __PixelType ) \
  printf( "\n\n%6sChecking outputs ...\n", "" ); \
  spOutputImage->Fill( static_cast< OutputPixelType >( 0 ) ); \
  std::string strRefHandlerName; \
  for (auto itHandler : lstHandlers) { \
    if (itHandler == lstHandlers.front()) { \
      strRefHandlerName = itHandler->GetName(); \
      itHandler->Launch( spOutputImage, x0, y0, (x1 - x0) / spOutputImage->GetWidth(), (y1 - y0) / spOutputImage->GetHeight(), count ); \
    } else { \
      CREATE_IMAGE( OutputImageType, spCompImage ); \
      itHandler->Launch( spCompImage, x0, y0, (x1 - x0) / spOutputImage->GetWidth(), (y1 - y0) / spOutputImage->GetHeight(), count ); \
      printf( "\n%8s\"%10s\"  <-->  \"%14s\"  =  %5.3e", "", strRefHandlerName.c_str(), itHandler->GetName().c_str(), spOutputImage->MaxDeviation( *spCompImage ) ); \
      ImageIO::SaveImage( "Comp_Mandelbrot_" #__PixelType ".xsc", *spCompImage ); \
    } \
  } \
  ImageIO::SaveImage( "Out_Mandelbrot_" #__PixelType ".xsc", *spOutputImage ); \
  printf("\n");

#else

#define TEST_RUN_COUNT  100

#endif

#endif // _MANDELBROT_DEFINES_H_
