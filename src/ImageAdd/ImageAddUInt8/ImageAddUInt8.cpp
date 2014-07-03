#include "stdafx.h"
#include "../../include/ImageAdd/ImageAdd.h"
#include "ImageAddUInt8Handlers.h"
#include <omp.h>


void ImageAdd::_RunUInt8()
{
  const size_t cszIters = static_cast< size_t >( 100 );

  printf("\n    Running \"_RunUInt8()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, ImageAddUInt8_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, ImageAddUInt8_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, ImageAddUInt8_GetAVXHandlers()    );

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


