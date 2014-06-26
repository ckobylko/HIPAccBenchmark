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
    addAccessor(&Input); \
  } \
\
  void kernel() \
  { \
    const InputPixelType_1 TRefVal = Input(0, 0); \
    bool  bMaximum = true, bMinimum = true; \
\
    for (int iY = -anchor; iY <= anchor; ++iY) \
    { \
      bool bBreak = false; \
\
      for (int iX = -anchor; iX <= anchor; ++iX) \
      { \
        /* Skip reference pixel */ \
        if ((iY == 0) && (iX == 0))     continue; \
\
        InputPixelType_1 TCurVal = Input(iY, iX); \
        if (TCurVal > TRefVal) \
        { \
          bMaximum = false; \
          if (! bMinimum) \
          { \
            bBreak = true; \
            break; \
          } \
        } \
        else if (TCurVal < TRefVal) \
        { \
          bMinimum = false; \
          if (! bMaximum) \
          { \
            bBreak = true; \
            break; \
          } \
        } \
      } \
\
      if (bBreak)  break; \
    } \
\
    OutputPixelType TOutVal =    0; \
    if (bMaximum)   TOutVal += 128; \
    if (bMinimum)   TOutVal +=  64; \
\
    output() = TOutVal;\
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
  pOutputData = Output.getData(); \
\
  /* memory clean-up*/ \
  free(pInputData); \
  free(pOutputData); \
\
  return 0; \
} \


