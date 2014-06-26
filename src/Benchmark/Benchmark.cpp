// Benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../include/ImageAdd/ImageAdd.h"
#include "../../include/NormalizedGradient/NormalizedGradient.h"
#include "../../include/MinMaxDetector/MinMaxDetector.h"


int _tmain(int argc, _TCHAR* argv[])
{
  ImageAdd::Run();

  NormalizedGradient::Run();

  MinMaxDetector::Run();

  return 0;
}

