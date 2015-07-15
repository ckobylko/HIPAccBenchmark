#include "TestRead.h"
#include "TestWrite.h"
#include <immintrin.h>
#include <omp.h>
using namespace MemoryThroughputTest;


double TestRead::_RunUInt8_AVX(unsigned char *pucData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 32 / static_cast< int >( sizeof( unsigned char ) );

  _mm256_zeroall();

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        __m256       mmAccumulator = _mm256_setzero_ps();
        unsigned char *pucLine      = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          __m256i mmCurVal  = _mm256_load_si256( reinterpret_cast<const __m256i*>( pucLine + iX) );
          mmAccumulator     = _mm256_xor_ps( mmAccumulator, _mm256_castsi256_ps( mmCurVal ) );
        }

        _mm256_store_si256( reinterpret_cast<__m256i*>( pucLine ), _mm256_castps_si256( mmAccumulator ) );
      }
    }
    else
    {
      __m256 mmAccumulator = _mm256_setzero_ps();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          __m256i mmCurVal  = _mm256_load_si256( reinterpret_cast<const __m256i*>( pucLine + iX) );
          mmAccumulator     = _mm256_xor_ps( mmAccumulator, _mm256_castsi256_ps( mmCurVal ) );
        }
      }

      _mm256_store_si256( reinterpret_cast<__m256i*>( pucData ), _mm256_castps_si256( mmAccumulator ) );
    }
  }

  _mm256_zeroupper();

  return omp_get_wtime() - dTime;
}

double TestRead::_RunFloat_AVX(float *pfData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 32 / static_cast< int >( sizeof( float ) );

  _mm256_zeroall();

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        __m256  mmAccumulator = _mm256_setzero_ps();
        float   *pfLine       = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm256_xor_ps( mmAccumulator, _mm256_load_ps(pfLine + iX) );
        }

        _mm256_store_ps( pfLine, mmAccumulator );
      }
    }
    else
    {
      __m256 mmAccumulator = _mm256_setzero_ps();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          mmAccumulator = _mm256_xor_ps( mmAccumulator, _mm256_load_ps(pfLine + iX) );
        }
      }

      _mm256_store_ps( pfData, mmAccumulator );
    }
  }

  _mm256_zeroupper();

  return omp_get_wtime() - dTime;
}


double TestWrite::_RunUInt8_AVX(unsigned char *pucData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 32 / static_cast< int >( sizeof( unsigned char ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        _mm256_zeroall();

        const __m256i cmmWriteValue = _mm256_setzero_si256();
        unsigned char *pucLine      = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm256_stream_si256( reinterpret_cast< __m256i * >( pucLine + iX ), cmmWriteValue );
        }

        _mm256_zeroupper();
        _mm_sfence();
      }
    }
    else
    {
      _mm256_zeroall();

      const __m256i cmmWriteValue = _mm256_setzero_si256();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        unsigned char *pucLine = pucData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm256_stream_si256( reinterpret_cast< __m256i * >( pucLine + iX ), cmmWriteValue );
        }
      }

      _mm256_zeroupper();
      _mm_sfence();
    }
  }

  return omp_get_wtime() - dTime;
}

double TestWrite::_RunFloat_AVX(float *pfData, bool bParallel)
{
  const int ciWidth       = static_cast< int >( _cszWidth  );
  const int ciHeight      = static_cast< int >( _cszHeight );
  const int ciVectorWidth = 32 / static_cast< int >( sizeof( float ) );

  double dTime = omp_get_wtime();

  for (unsigned int uiIter = 0; uiIter < _cuiIters; ++uiIter)
  {
    if (bParallel)
    {
      #pragma omp parallel for
      for (int iY = 0; iY < ciHeight; ++iY)
      {
        _mm256_zeroall();

        const __m256 cmmWriteValue = _mm256_setzero_ps();
        float *pfLine               = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm256_stream_ps( pfLine + iX, cmmWriteValue );
        }

        _mm256_zeroupper();
        _mm_sfence();
      }
    }
    else
    {
      _mm256_zeroall();

      const __m256 cmmWriteValue = _mm256_setzero_ps();

      for (int iY = 0; iY < ciHeight; ++iY)
      {
        float *pfLine = pfData + (iY * ciWidth);

        for (int iX = 0; iX < ciWidth; iX += ciVectorWidth)
        {
          _mm256_stream_ps( pfLine + iX, cmmWriteValue );
        }
      }

      _mm256_zeroupper();
      _mm_sfence();
    }
  }

  return omp_get_wtime() - dTime;
}


