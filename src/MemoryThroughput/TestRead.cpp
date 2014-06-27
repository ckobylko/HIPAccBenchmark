#include "stdafx.h"
#include "TestRead.h"
#include <map>
#include <omp.h>
#include <string>
using namespace MemoryThroughputTest;

double TestRead::_RunUInt8_Scalar(unsigned char *pucData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char ucAccumulator = 0;
        unsigned char *pucLine      = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          ucAccumulator ^= pucLine[ iX ];
        }

        *pucLine = ucAccumulator;
      }
    }
    else
    {
      unsigned char ucAccumulator = 0;

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          ucAccumulator ^= pucLine[ iX ];
        }
      }

      *pucData = ucAccumulator;
    }
  }

  return omp_get_wtime() - dTime;
}

double TestRead::_RunFloat_Scalar(float *pfData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float fAccumulator  = 0.f;
        float *pfLine       = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          fAccumulator += pfLine[ iX ];
        }

        *pfLine = fAccumulator;
      }
    }
    else
    {
      float fAccumulator = 0.f;

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          fAccumulator += pfLine[ iX ];
        }
      }

      *pfData = fAccumulator;
    }
  }

  return omp_get_wtime() - dTime;
}



template < typename PixelType >
void TestRead::_RunGeneric(const char *pcTestName, PixelType *pTData, bool bParallel)
{
  typedef std::map< std::string, double >   ResultMapType;

  const size_t cszDataSize    = _cszWidth * _cszHeight * sizeof( PixelType );
  const int    ciDataSizeMB   = static_cast< int >( cszDataSize ) / ( 1 << 20 );
  const int    ciThreadCount  = bParallel ? omp_get_num_procs() : 1;

  printf("\n      Running \"%s\"  (%d MB, %d threads):\n", pcTestName, ciDataSizeMB, ciThreadCount);

  omp_set_num_threads( ciThreadCount );

  ResultMapType mapResults;

  mapResults[ "1-Scalar" ]  = _RunGeneric_Scalar( pTData, bParallel );
  mapResults[ "2-SSE" ]     = _RunGeneric_SSE   ( pTData, bParallel );
  mapResults[ "3-AVX" ]     = _RunGeneric_AVX   ( pTData, bParallel );

  for (auto itResult : mapResults)
  {
    itResult.second     /= static_cast<double>(_cuiIters);
    double dThroughput   = static_cast<double>(ciDataSizeMB) / (itResult.second * 1000.);
    printf( "\n        Throughput for \"%8s\"  =  %6.3f GB/s", itResult.first.c_str(), dThroughput );
  }

  printf("\n");
}


void TestRead::RunUInt8(unsigned char *pucData, bool bParallel)
{
  _RunGeneric("RunUInt8", pucData, bParallel);
}

void TestRead::RunFloat(float *pfData, bool bParallel)
{
  _RunGeneric("RunFloat", pfData, bParallel);
}


