// Benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../include/ImageAdd/ImageAdd.h"
#include "../../include/NormalizedGradient/NormalizedGradient.h"
#include "../../include/MinMaxDetector/MinMaxDetector.h"
#include "../../include/TopologicalErosion/TopologicalErosion.h"
#include <stdexcept>


int _tmain(int argc, _TCHAR* argv[])
{
  try
  {
    ImageAdd::Run();

    NormalizedGradient::Run();

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      MinMaxDetector::Run( uiKernelSize );
    }

    for (unsigned int uiKernelSize = 3; uiKernelSize <= 9; uiKernelSize += 2)
    {
      TopologicalErosion::Run(uiKernelSize);
    }
  }
  catch (std::exception &e)
  {
    printf( "\n\nERROR: %s\n\n", e.what() );
  }

  return 0;
}

