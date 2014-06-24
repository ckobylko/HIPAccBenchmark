#include "stdafx.h"
#include "../../../include/ImageAdd/ImageAdd.h"
#include "ImageAddIntHandlers.h"
#include <omp.h>


void ImageAdd::_RunInt()
{
  const size_t cszIters = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunInt()\"\n");

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, ImageAddInt_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, ImageAddInt_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, ImageAddInt_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType1, spInputImage1 );
  CREATE_IMAGE( InputImageType2, spInputImage2 );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      itHandler->Launch(spOutputImage, spInputImage1, spInputImage2);
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }

  printf("\n");
}


