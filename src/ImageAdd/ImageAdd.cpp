#include "../../include/ImageAdd/ImageAdd.h"
#include <stdio.h>

void ImageAdd::Run()
{
  printf("\n  Running \"ImageAdd\":\n");

  _RunFloat();

  _RunInt();

  _RunUInt8();

  printf("\n");
}

