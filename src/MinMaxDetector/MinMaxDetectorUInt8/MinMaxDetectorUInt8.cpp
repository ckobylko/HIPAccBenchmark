#include "stdafx.h"
#include "../../include/MinMaxDetector/MinMaxDetector.h"
#include "MinMaxDetectorUInt8Handlers.h"
#include <omp.h>


void MinMaxDetector::_RunUInt8(unsigned int uiKernelSize)
{
  const size_t        cszIters      = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunUInt8()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, MinMaxDetectorUInt8_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, MinMaxDetectorUInt8_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, MinMaxDetectorUInt8_GetAVXHandlers()    );

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

