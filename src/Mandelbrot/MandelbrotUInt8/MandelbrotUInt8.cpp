#include "../MandelbrotDefines.h"
#include "MandelbrotUInt8Handlers.h"


void Mandelbrot::_RunUInt8()
{
  const size_t cszIters = static_cast< size_t >( TEST_RUN_COUNT );

  printf("\n    Running \"_RunUInt8()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, MandelbrotUInt8_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, MandelbrotUInt8_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, MandelbrotUInt8_GetAVXHandlers()    );

  CREATE_IMAGE( OutputImageType, spOutputImage );

  const float x0    =  -2.;
  const float x1    =   1.;
  const float y0    = - 1.;
  const float y1    =   1.;
  const int   count = 256;


  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%14s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      _mm256_zeroall();
      itHandler->Launch( spOutputImage, x0, y0, (x1 - x0) / spOutputImage->GetWidth(), (y1 - y0) / spOutputImage->GetHeight(), count );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }


#ifdef CONFIG_CHECK_OUTPUT

  MANDELBROT_CHECK_OUTPUT( UInt8 );

#endif


  printf("\n");
}


