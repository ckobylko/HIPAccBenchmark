#define _CRT_SECURE_NO_WARNINGS

#include "../../include/Benchmark/ImageIO.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>


void ImageIO::_LoadTestImage(unsigned char *pucBuffer)
{
  const char *pcTestFilename = "Lenna.raw";

  int iInFile = _open( pcTestFilename, O_BINARY | O_RDONLY, _S_IREAD );

  _read( iInFile, pucBuffer, TEST_IMAGE_WIDTH * TEST_IMAGE_HEIGHT );

  _close(iInFile);
}


void ImageIO::_SaveImage(const char *pcFilename, const unsigned short *pusBuffer, unsigned int uiWidth, unsigned int uiHeight)
{
  int iOutFile = _open( pcFilename, O_CREAT | O_TRUNC | O_BINARY | O_RDWR, _S_IREAD | _S_IWRITE );

  const unsigned short usWidth  = static_cast< unsigned short >( uiWidth  );
  const unsigned short usHeight = static_cast< unsigned short >( uiHeight );

  _write( iOutFile, &usWidth,  2 );
  _write( iOutFile, &usHeight, 2 );

  _write( iOutFile, pusBuffer, uiWidth * uiHeight * 2 );

  _commit( iOutFile );
  _close( iOutFile );
}

