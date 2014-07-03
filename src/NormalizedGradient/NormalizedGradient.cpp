#include "stdafx.h"
#include "../../include/NormalizedGradient/NormalizedGradient.h"

void NormalizedGradient::Run()
{
  printf("\n  Running \"NormalizedGradient\":\n");

  _RunFloat();

  _RunUInt8();

  printf("\n");
}

