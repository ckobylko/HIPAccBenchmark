#include "../BubbleSortMedianDefines.h"
#include "BubbleSortMedianUInt8Handlers.h"


void BubbleSortMedian::_RunUInt8(unsigned int uiKernelSize)
{
  const size_t cszIters = static_cast< size_t >( TEST_RUN_COUNT );

  printf("\n    Running \"_RunUInt8()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, BubbleSortMedianUInt8_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, BubbleSortMedianUInt8_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, BubbleSortMedianUInt8_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType,  spInputImage  );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  ImageIO::LoadTestImage( *spInputImage );

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


#ifdef CONFIG_CHECK_OUTPUT

  BUBBLE_SORT_MEDIAN_CHECK_OUTPUT( UInt8 );

#endif


  printf("\n");
}


