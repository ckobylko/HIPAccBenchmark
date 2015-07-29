#include "../NormalizedGradientDefines.h"
#include "NormalizedGradientFloatHandlers.h"


void NormalizedGradient::_RunFloat()
{
  const size_t cszIters = static_cast< size_t >( TEST_RUN_COUNT );

  printf("\n    Running \"_RunFloat()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, NormalizedGradientFloat_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType1, spInputImage1  );
  CREATE_IMAGE( InputImageType2, spInputImage2  );
  CREATE_IMAGE( OutputImageType, spOutputImage1 );
  CREATE_IMAGE( OutputImageType, spOutputImage2 );

  // Generate gradient images (by 3x3 Sobel filter)
  {
    MAKE_IMAGE_TYPE( TestImageType, double, ciImageWidth, ciImageHeight );
    CREATE_IMAGE( TestImageType, spTestImage );
    ImageIO::LoadTestImage( *spTestImage );

    for (int iY = 1; iY < TestImageType::GetHeight() - 1; ++iY)
    {
      for (int iX = 1; iX < TestImageType::GetWidth() - 1; ++iX)
      {
        double dGradX = 0.;
        double dGradY = 0.;

        for (int iOff = -1; iOff <= 1; ++iOff)
        {
          const double cdMultiplier = (iOff == 0) ? 2. : 1.;

          dGradX += ( spTestImage->Data[ iY + iOff ][ iX +    1 ] - spTestImage->Data[ iY + iOff ][ iX -    1 ] ) * cdMultiplier;
          dGradY += ( spTestImage->Data[ iY +    1 ][ iX + iOff ] - spTestImage->Data[ iY -    1 ][ iX + iOff ] ) * cdMultiplier;
        }

        spInputImage1->Data[ iY ][ iX ] = static_cast< InputPixelType_1 >( dGradX / 8. );
        spInputImage2->Data[ iY ][ iX ] = static_cast< InputPixelType_2 >( dGradY / 8. );
      }
    }
  }


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


#ifdef CONFIG_CHECK_OUTPUT

  NORMALIZED_GRADIENT_CHECK_OUTPUT( Float );

#endif


  printf("\n");
}


