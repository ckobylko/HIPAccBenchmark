#include "TestRead.h"
#include "TestWrite.h"
#include <nmmintrin.h>
#include <omp.h>
using namespace MemoryThroughputTest;


double TestRead::_RunUInt8_SSE(unsigned char *pucData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 16 / static_cast< int >( sizeof( unsigned char ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        __m128i       mmAccumulator = _mm_setzero_si128();
        unsigned char *pucLine      = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm_xor_si128( mmAccumulator, _mm_load_si128( reinterpret_cast<const __m128i*>( pucLine + iX) ) );
        }

        _mm_store_si128( reinterpret_cast<__m128i*>( pucLine ), mmAccumulator );
      }
    }
    else
    {
      __m128i mmAccumulator = _mm_setzero_si128();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm_xor_si128( mmAccumulator, _mm_load_si128( reinterpret_cast<const __m128i*>( pucLine + iX) ) );
        }
      }

      _mm_store_si128( reinterpret_cast<__m128i*>( pucData ), mmAccumulator );
    }
  }

  return omp_get_wtime() - dTime;
}

double TestRead::_RunFloat_SSE(float *pfData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 16 / static_cast< int >( sizeof( float ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        __m128  mmAccumulator = _mm_setzero_ps();
        float   *pfLine       = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm_xor_ps( mmAccumulator, _mm_load_ps(pfLine + iX) );
        }

        _mm_store_ps( pfLine, mmAccumulator );
      }
    }
    else
    {
      __m128 mmAccumulator = _mm_setzero_ps();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm_xor_ps( mmAccumulator, _mm_load_ps(pfLine + iX) );
        }
      }

      _mm_store_ps( pfData, mmAccumulator );
    }
  }

  return omp_get_wtime() - dTime;
}


double TestWrite::_RunUInt8_SSE(unsigned char *pucData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 16 / static_cast< int >( sizeof( unsigned char ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        const __m128i cmmWriteValue = _mm_setzero_si128();
        unsigned char *pucLine      = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm_stream_si128( reinterpret_cast< __m128i * >( pucLine + iX ), cmmWriteValue );
        }

        _mm_sfence();
      }
    }
    else
    {
      const __m128i cmmWriteValue = _mm_setzero_si128();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm_stream_si128( reinterpret_cast< __m128i * >( pucLine + iX ), cmmWriteValue );
        }
      }

      _mm_sfence();
    }
  }

  return omp_get_wtime() - dTime;
}

double TestWrite::_RunFloat_SSE(float *pfData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 16 / static_cast< int >( sizeof( float ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        const __m128 cmmWriteValue  = _mm_setzero_ps();
        float *pfLine               = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm_stream_ps( pfLine + iX, cmmWriteValue );
        }

        _mm_sfence();
      }
    }
    else
    {
      const __m128 cmmWriteValue = _mm_setzero_ps();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm_stream_ps( pfLine + iX, cmmWriteValue );
        }
      }

      _mm_sfence();
    }
  }

  return omp_get_wtime() - dTime;
}


