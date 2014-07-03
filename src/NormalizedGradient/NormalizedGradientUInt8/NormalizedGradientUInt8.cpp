#include "stdafx.h"
#include "../../../include/NormalizedGradient/NormalizedGradient.h"
#include "NormalizedGradientUInt8Handlers.h"
#include <omp.h>


void NormalizedGradient::_RunUInt8()
{
  const size_t cszIters = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunUInt8()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, NormalizedGradientUInt8_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, NormalizedGradientUInt8_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, NormalizedGradientUInt8_GetAVXHandlers()    );

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
      itHandler->Launch( spOutputImage1, spOutputImage2, spInputImage1, spInputImage2 );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


