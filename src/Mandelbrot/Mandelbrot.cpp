#include "../../include/Mandelbrot/Mandelbrot.h"
#include <stdexcept>
#include <stdio.h>

void Mandelbrot::Run()
{
  printf( "\n  Running \"Mandelbrot\":\n" );

  _RunUInt8();

  printf("\n");
}

