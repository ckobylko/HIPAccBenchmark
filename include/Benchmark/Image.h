#ifndef _BENCHMARK_IMAGE_H_
#define _BENCHMARK_IMAGE_H_

#include <algorithm>
#include <cmath>
#include <memory>

template < typename PixelType, const int ciWidth, const int ciHeight >
class Image
{
public:

  typedef PixelType PixelType;

  enum
  {
    Width  = ciWidth,
    Height = ciHeight
  };


  PixelType Data[ Height ][ Width ];


  inline static std::shared_ptr< Image > Create()
  {
    std::shared_ptr< Image >  spImage = std::make_shared< Image >();

    spImage->Fill( static_cast< PixelType >( 0 ) );

    return spImage;
  }

  inline static int GetWidth()    { return Width; }
  inline static int GetHeight()   { return Height; }


  void Fill(PixelType TFillValue)
  {
    for (int iY = 0; iY < GetHeight(); ++iY)
    {
      for (int iX = 0; iX < GetWidth(); ++iX)
      {
        Data[ iY ][ iX ] = TFillValue;
      }
    }
  }


  double MaxDeviation(const Image &crCompImage)
  {
    double dMaxDev = std::abs( static_cast< double >( Data[0][0] ) - static_cast< double >( crCompImage.Data[0][0] ) );

    for (int iY = 0; iY < GetHeight(); ++iY)
    {
      for (int iX = 0; iX < GetWidth(); ++iX)
      {
        const double dRefVal  = static_cast< double >(             Data[ iY ][ iX ] );
        const double dCompVal = static_cast< double >( crCompImage.Data[ iY ][ iX ] );

        dMaxDev = std::max( dMaxDev, std::abs( dRefVal - dCompVal ) );
      }
    }

    return dMaxDev;
  }
};


#define MAKE_IMAGE_TYPE(__Name, __PixelType, __Width, __Height) \
  typedef Image< __PixelType, __Width, __Height >   __Name; \
  typedef std::shared_ptr< __Name >   __Name##Ptr;


#define CREATE_IMAGE(__ImageType, __VarName) \
  __ImageType##Ptr __VarName = __ImageType::Create();


#endif //_BENCHMARK_IMAGE_H_
