#include "hipacc.hpp"
#include <stdlib.h>

#ifndef KERNEL_NAME
static_assert(false, "Define the KERNEL_NAME property");
#endif

// This is the only way to force HIPAcc to include the kernel
#define IMPORT_KERNEL() \
  \
class KERNEL_NAME : public hipacc::Kernel<OutputPixelType> \
{ \
private: \
  hipacc::Accessor<InputPixelType_1> &Input; \
  const int anchor; \
  \
public: \
  KERNEL_NAME(hipacc::IterationSpace<OutputPixelType> &Iter, hipacc::Accessor<InputPixelType_1> &InputImg, const int ciAnchor) : \
                  Kernel(Iter), Input(InputImg), anchor(ciAnchor) \
  { \
    add_accessor(&Input); \
  } \
\
  void kernel() \
  { \
    InputPixelType_1 TOutVal = Input(0, 0); \
\
    for (int iY = -anchor; iY <= anchor; ++iY) \
    { \
      for (int iX = -anchor; iX <= anchor; ++iX) \
      { \
        InputPixelType_1 TCurVal = Input(iX, iY); \
        TOutVal = min( TOutVal, TCurVal ); \
      } \
    } \
\
    output() = static_cast< OutputPixelType >( TOutVal );\
  } \
}; \
\
\
int main(int argc, const char **argv) \
{ \
  const size_t cszMemorySize = static_cast< size_t >(ciImageWidth * ciImageHeight); \
  const int    ciAnchor = 3; \
\
  /* host memory for image of width x height pixels*/ \
  InputPixelType_1  *pInputData  = (InputPixelType_1*) calloc( cszMemorySize, sizeof(InputPixelType_1) ); \
  OutputPixelType   *pOutputData = (OutputPixelType*)  calloc( cszMemorySize, sizeof(OutputPixelType)  ); \
\
  /* Create input and output images*/ \
  hipacc::Image< InputPixelType_1 >           Input (ciImageWidth, ciImageHeight); \
  hipacc::Image< OutputPixelType  >           Output(ciImageWidth, ciImageHeight); \
  hipacc::IterationSpace< OutputPixelType >   Iter( Output, ciImageWidth - ciAnchor * 2, ciImageHeight - ciAnchor * 2, ciAnchor, ciAnchor ); \
\
  /* Set inputs*/ \
  Input  = pInputData; \
  Output = pOutputData; \
\
  /* Create and execute filter */ \
  hipacc::Accessor< InputPixelType_1 > accInput( Input, ciImageWidth - ciAnchor * 2, ciImageHeight - ciAnchor * 2, ciAnchor, ciAnchor ); \
  KERNEL_NAME filter(Iter, accInput, ciAnchor); \
  filter.execute(); \
\
  /* get results*/ \
  pOutputData = Output.data(); \
\
  /* memory clean-up*/ \
  free(pInputData); \
  free(pOutputData); \
\
  return 0; \
} \


