#include "hipacc.hpp"
#include <stdlib.h>

#ifndef KERNEL_NAME
static_assert(false, "Define the KERNEL_NAME property");
#endif

// This is the only way to force HIPAcc to include the kernel
#define IMPORT_KERNEL() \
  \
/* Kernel description in HIPAcc */ \
class KERNEL_NAME : public hipacc::Kernel< OutputPixelType > \
{\
private:\
  int count; \
  float x0, y0, dx, dy; \
  \
public:\
  KERNEL_NAME(hipacc::IterationSpace<OutputPixelType> &iter, float x0, float y0, float dx, float dy, int count) : \
              Kernel(iter), count(count), x0(x0), y0(y0), dx(dx), dy(dy) \
  {\
  }\
  \
  void kernel() \
  {\
    OutputPixelType out = 0; \
    float c_re = x() * dx + x0; \
    float c_im = y() * dy + y0; \
\
    float z_re = c_re, z_im = c_im; \
    for (int i = 0; i < count; ++i) \
    { \
        if (z_re * z_re + z_im * z_im > 4.f) \
        { \
            out = (OutputPixelType)i; \
            break; \
        } \
        float new_re = z_re*z_re - z_im*z_im; \
        float new_im = 2.f * z_re * z_im; \
        z_re = c_re + new_re; \
        z_im = c_im + new_im; \
    } \
    output() = out; \
  }\
};\
\
\
int main(int argc, const char **argv) \
{ \
  const size_t cszMemorySize = static_cast< size_t >(ciImageWidth * ciImageHeight); \
\
  /* host memory for image of width x height pixels*/ \
  OutputPixelType   *pOutputData = (OutputPixelType*)  calloc( cszMemorySize, sizeof(OutputPixelType)  ); \
\
  /* Create input and output images*/ \
  hipacc::Image< OutputPixelType  >           Output(ciImageWidth, ciImageHeight); \
  hipacc::IterationSpace< OutputPixelType >   Iter( Output, ciImageWidth, ciImageHeight ); \
\
  /* Set inputs*/ \
  Output = pOutputData; \
\
  /* Create and execute filter */ \
  float x0 = -2.; \
  float x1 =  1.; \
  float y0 = -1.; \
  float y1 =  1.; \
  KERNEL_NAME filter(Iter, x0, y0, (x1 - x0) / ciImageWidth, (y1 - y0) / ciImageHeight, 256); \
  filter.execute(); \
\
  /* get results*/ \
  pOutputData = Output.data(); \
\
  /* memory clean-up*/ \
  free(pOutputData); \
\
  return 0; \
} \


