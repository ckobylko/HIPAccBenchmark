#pragma once

#include "Image.h"


#define TEST_IMAGE_WIDTH  512
#define TEST_IMAGE_HEIGHT 512


class ImageIO
{
private:

  static void _LoadTestImage(unsigned char *pucBuffer);

  static void _SaveImage(const char *pcFilename, const unsigned short *pusBuffer, unsigned int uiWidth, unsigned int uiHeight);


public:

  template < typename ImageType >
  inline static void LoadTestImage(ImageType &rImage)
  {
    static_assert( (ImageType::Width  & TEST_IMAGE_WIDTH ) == 0, "The image width must be dividible by the test image width!" );
    static_assert( (ImageType::Height & TEST_IMAGE_HEIGHT) == 0, "The image height must be dividible by the test image height!" );

    MAKE_IMAGE_TYPE( BufferImageType, unsigned char, TEST_IMAGE_WIDTH, TEST_IMAGE_HEIGHT );

    CREATE_IMAGE( BufferImageType, spBufferImage );

    _LoadTestImage( spBufferImage->Data[0] );


    const int ciSpreadWidth  = ImageType::GetWidth()  / TEST_IMAGE_WIDTH;
    const int ciSpreadHeight = ImageType::GetHeight() / TEST_IMAGE_HEIGHT;

    for (int iY = 0; iY < TEST_IMAGE_HEIGHT; ++iY)
    {
      unsigned char *pucBufferLine = spBufferImage->Data[iY];

      for (int iX = 0; iX < TEST_IMAGE_WIDTH; ++iX)
      {
        const typename ImageType::PixelType cTPixelVal = static_cast< typename ImageType::PixelType >( pucBufferLine[ iX ] );

        for (int iOutY = 0; iOutY < ciSpreadHeight; ++iOutY)
        {
          for (int iOutX = 0; iOutX < ciSpreadWidth; ++iOutX)
          {
            rImage.Data[ iY * ciSpreadHeight + iOutY ][ iX * ciSpreadWidth + iOutX ] = cTPixelVal;
          }
        }
      }
    }
  }


  template < typename ImageType >
  inline static void SaveImage(const char *pcFilename, const ImageType &crImage)
  {
    MAKE_IMAGE_TYPE( BufferImageType, unsigned short, ImageType::Width, ImageType::Height );

    CREATE_IMAGE( BufferImageType, spBufferImage );

    for (int iY = 0; iY < ImageType::GetHeight(); ++iY)
    {
      unsigned short *pusBufferLine = spBufferImage->Data[ iY ];

      for (int iX = 0; iX < ImageType::GetWidth(); ++iX)
      {
        pusBufferLine[ iX ] = static_cast< unsigned short >( crImage.Data[ iY ][ iX ] );
      }
    }

    _SaveImage( pcFilename, spBufferImage->Data[0], ImageType::GetWidth(), ImageType::GetHeight() );
  }

};