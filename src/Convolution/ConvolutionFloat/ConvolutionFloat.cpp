#include "stdafx.h"
#include "../../include/Convolution/Convolution.h"
#include "ConvolutionFloatHandlers.h"
#include <omp.h>


void Convolution::_RunFloat(unsigned int uiKernelSize)
{
  const size_t        cszIters      = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunFloat()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, ConvolutionFloat_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, ConvolutionFloat_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, ConvolutionFloat_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType,  spInputImage  );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      itHandler->Launch( spOutputImage, spInputImage, uiKernelSize );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


