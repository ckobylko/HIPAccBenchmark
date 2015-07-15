#include "TestWrite.h"
#include <map>
#include <omp.h>
#include <string>
using namespace MemoryThroughputTest;


double TestWrite::_RunUInt8_Scalar(unsigned char *pucData, bool bParallel)
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
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          pucLine[ iX ] = 0;
        }
      }
    }
    else
    {
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          pucLine[ iX ] = 0;
        }
      }
    }
  }

  return omp_get_wtime() - dTime;
}

double TestWrite::_RunFloat_Scalar(float *pfData, bool bParallel)
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
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          pfLine[ iX ] = 0.f;
        }
      }
    }
    else
    {
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; ++iX)
        {
          pfLine[ iX ] = 0.f;
        }
      }
    }
  }

  return omp_get_wtime() - dTime;
}



template < typename PixelType >
void TestWrite::_RunGeneric(const char *pcTestName, PixelType *pTData, bool bParallel)
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


void TestWrite::RunUInt8(unsigned char *pucData, bool bParallel)
{
  _RunGeneric("RunUInt8", pucData, bParallel);
}

void TestWrite::RunFloat(float *pfData, bool bParallel)
{
  _RunGeneric("RunFloat", pfData, bParallel);
}


