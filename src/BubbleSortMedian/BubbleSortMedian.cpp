#include "stdafx.h"
#include "../../include/BubbleSortMedian/BubbleSortMedian.h"
#include <stdexcept>

void BubbleSortMedian::Run(unsigned int uiKernelSize)
{
  if (uiKernelSize < 3)
  {
    throw std::runtime_error( "The kernel size must be greater than or equal to 3!" );
  }
  else if ((uiKernelSize & 1) == 0)
  {
    throw std::runtime_error("The kernel size must be odd!");
  }

  printf( "\n  Running \"BubbleSortMedian\" - Kernel-size= %d:\n", uiKernelSize );

  _RunFloat( uiKernelSize );

  _RunUInt8( uiKernelSize );

  printf("\n");
}

