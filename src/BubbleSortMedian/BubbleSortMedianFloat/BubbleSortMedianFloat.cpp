#include "stdafx.h"
#include "../../include/BubbleSortMedian/BubbleSortMedian.h"
#include "BubbleSortMedianFloatHandlers.h"
#include <omp.h>


void BubbleSortMedian::_RunFloat(unsigned int uiKernelSize)
{
  const size_t        cszIters      = static_cast< size_t >( (uiKernelSize <= 5) ? 100 : 10 );

  printf("\n    Running \"_RunFloat()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, BubbleSortMedianFloat_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, BubbleSortMedianFloat_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, BubbleSortMedianFloat_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType,  spInputImage  );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      _mm256_zeroall();
      itHandler->Launch( spOutputImage, spInputImage, uiKernelSize );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


