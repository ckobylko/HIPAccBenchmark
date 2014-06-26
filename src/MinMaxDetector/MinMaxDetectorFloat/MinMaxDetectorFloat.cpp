#include "stdafx.h"
#include "../../include/MinMaxDetector/MinMaxDetector.h"
#include "MinMaxDetectorFloatHandlers.h"
#include <omp.h>


void MinMaxDetector::_RunFloat()
{
  const size_t        cszIters      = static_cast< size_t >( 100 );
  const unsigned int  cuiKernelSize = 3;

  printf("\n    Running \"_RunFloat()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, MinMaxDetectorFloat_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, MinMaxDetectorFloat_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, MinMaxDetectorFloat_GetAVXHandlers()     );

  CREATE_IMAGE( InputImageType,  spInputImage  );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      itHandler->Launch( spOutputImage, spInputImage, cuiKernelSize );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


