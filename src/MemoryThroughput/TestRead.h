#pragma once

namespace MemoryThroughputTest
{
  class TestRead
  {
  private:

    const unsigned int  _cuiIters;
    const size_t        _cszWidth, _cszHeight;


    double _RunUInt8_Scalar(unsigned char *pucData, bool bParallel);

    double _RunUInt8_SSE(unsigned char *pucData, bool bParallel);

    double _RunUInt8_AVX(unsigned char *pucData, bool bParallel);


    double _RunFloat_Scalar(float *pfData, bool bParallel);

    double _RunFloat_SSE(float *pfData, bool bParallel);

    double _RunFloat_AVX(float *pfData, bool bParallel);



    template <typename PixelType>   inline double _RunGeneric_Scalar(PixelType     *pTData, bool bParallel);
    template <>                     inline double _RunGeneric_Scalar(unsigned char *pTData, bool bParallel)  { return _RunUInt8_Scalar(pTData, bParallel); }
    template <>                     inline double _RunGeneric_Scalar(float         *pTData, bool bParallel)  { return _RunFloat_Scalar(pTData, bParallel); }

    template <typename PixelType>   inline double _RunGeneric_SSE(PixelType     *pTData, bool bParallel);
    template <>                     inline double _RunGeneric_SSE(unsigned char *pTData, bool bParallel)  { return _RunUInt8_SSE(pTData, bParallel); }
    template <>                     inline double _RunGeneric_SSE(float         *pTData, bool bParallel)  { return _RunFloat_SSE(pTData, bParallel); }

    template <typename PixelType>   inline double _RunGeneric_AVX(PixelType     *pTData, bool bParallel);
    template <>                     inline double _RunGeneric_AVX(unsigned char *pTData, bool bParallel)  { return _RunUInt8_AVX(pTData, bParallel); }
    template <>                     inline double _RunGeneric_AVX(float         *pTData, bool bParallel)  { return _RunFloat_AVX(pTData, bParallel); }



    template < typename PixelType >
    void _RunGeneric(const char *pcTestName, PixelType *pTData, bool bParallel);


  public:

    inline TestRead(unsigned int uiIters, size_t szImageWidth, size_t szImageHeight) : _cuiIters(uiIters), _cszWidth(szImageWidth), _cszHeight(szImageHeight)   {}


    void RunUInt8(unsigned char *pucData, bool bParallel);

    void RunFloat(float *pfData, bool bParallel);
  };
}