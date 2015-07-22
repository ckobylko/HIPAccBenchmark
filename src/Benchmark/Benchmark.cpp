// Benchmark.cpp : Defines the entry point for the console application.
//

#include "../../include/MemoryThroughput/MemoryThroughput.h"
#include "../../include/ImageAdd/ImageAdd.h"
#include "../../include/NormalizedGradient/NormalizedGradient.h"
#include "../../include/BubbleSortMedian/BubbleSortMedian.h"
#include "../../include/BubbleSortMedianOptimized/BubbleSortMedianOptimized.h"
#include "../../include/Convolution/Convolution.h"
#include "../../include/MinMaxDetector/MinMaxDetector.h"
#include "../../include/TopologicalErosion/TopologicalErosion.h"

#include "../../include/Mandelbrot/Mandelbrot.h"

#include <stdexcept>
#include <stdio.h>


int main(int argc, char* argv[])
{
  try
  {
    MemoryThroughput::Run();

    // Pixel-wise operations
    ImageAdd::Run();

    NormalizedGradient::Run();

    // Kernel operations
    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      Convolution::Run(uiKernelSize);
    }

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      BubbleSortMedian::Run(uiKernelSize);
    }

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      BubbleSortMedianOptimized::Run(uiKernelSize);
    }

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      MinMaxDetector::Run( uiKernelSize );
    }

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      TopologicalErosion::Run(uiKernelSize);
    }

    // Running new tests
    Mandelbrot::Run();
  }
  catch (std::exception &e)
  {
    printf( "\n\nERROR: %s\n\n", e.what() );
  }

  return 0;
}

