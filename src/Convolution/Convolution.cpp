#include "../../include/Convolution/Convolution.h"
#include <stdexcept>
#include <stdio.h>

void Convolution::Run(unsigned int uiKernelSize)
{
  if (uiKernelSize < 3)
  {
    throw std::runtime_error( "The kernel size must be greater than or equal to 3!" );
  }
  else if ((uiKernelSize & 1) == 0)
  {
    throw std::runtime_error("The kernel size must be odd!");
  }

  printf( "\n  Running \"Convolution\" - Kernel-size= %d:\n", uiKernelSize );

  _RunFloat( uiKernelSize );

  _RunUInt8( uiKernelSize );

  printf("\n");
}

