#include "stdafx.h"
#include "../../include/TopologicalErosion/TopologicalErosion.h"
#include <stdexcept>

void TopologicalErosion::Run(unsigned int uiKernelSize)
{
  if (uiKernelSize < 3)
  {
    throw std::runtime_error( "The kernel size must be greater than or equal to 3!" );
  }
  else if ((uiKernelSize & 1) == 0)
  {
    throw std::runtime_error("The kernel size must be odd!");
  }

  printf( "\n  Running \"TopologicalErosion\" - Kernel-size= %d:\n", uiKernelSize );

  printf("\n");
}

