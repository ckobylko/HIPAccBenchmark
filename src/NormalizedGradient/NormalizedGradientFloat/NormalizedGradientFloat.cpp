#include "stdafx.h"
#include "../../../include/NormalizedGradient/NormalizedGradient.h"
#include "NormalizedGradientFloatHandlers.h"
#include <omp.h>


void NormalizedGradient::_RunFloat()
{
  const size_t cszIters = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunFloat()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType1, spInputImage1  );
  CREATE_IMAGE( InputImageType2, spInputImage2  );
  CREATE_IMAGE( OutputImageType, spOutputImage1 );
  CREATE_IMAGE( OutputImageType, spOutputImage2 );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      _mm256_zeroall();
      itHandler->Launch( spOutputImage1, spOutputImage2, spInputImage1, spInputImage2 );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


