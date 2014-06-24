#include "hipacc.hpp"
#include <stdlib.h>
#include <cmath>

#ifndef KERNEL_NAME
static_assert(false, "Define the KERNEL_NAME property");
#endif

// This is the only way to force HIPAcc to include the kernel
#define IMPORT_KERNEL() \
  \
  \
using namespace hipacc; \
  \
  \
/* Kernel description in HIPAcc */ \
class KERNEL_NAME : public Kernel< OutputPixelType > \
{\
private:\
  Accessor<InputPixelType_1> &Input1;\
  Accessor<InputPixelType_2> &Input2;\
  \
public:\
  KERNEL_NAME(IterationSpace<OutputPixelType> &iter, Accessor<InputPixelType_1> &input1, Accessor<InputPixelType_2> &input2) : Kernel(iter), Input1(input1), Input2(input2)\
  {\
    addAccessor( &Input1 );\
    addAccessor( &Input2 );\
  }\
  \
  void kernel() {\
    output() = Input1(0, 0) + Input2(0, 0);\
  }\
};\
  \
  \
int main(int argc, const char **argv)\
{\
  const size_t cszMemorySize = static_cast< size_t >( ciImageWidth * ciImageHeight );\
  \
  /* host memory for image of width x height pixels*/ \
  InputPixelType_1  *pInputData1  = (InputPixelType_1*) calloc( cszMemorySize, sizeof(InputPixelType_1) );\
  InputPixelType_2  *pInputData2  = (InputPixelType_2*) calloc( cszMemorySize, sizeof(InputPixelType_2) );\
  OutputPixelType   *pOutputData  = (OutputPixelType*)  calloc( cszMemorySize, sizeof(OutputPixelType)  );\
  \
  /* Create input and output images*/ \
  Image< InputPixelType_1 >           Input1( ciImageWidth, ciImageHeight );\
  Image< InputPixelType_2 >           Input2( ciImageWidth, ciImageHeight );\
  Image< OutputPixelType  >           Output( ciImageWidth, ciImageHeight );\
  IterationSpace< OutputPixelType >   Iter( Output, ciImageWidth, ciImageHeight );\
  \
  /* Set inputs*/ \
  Input1 = pInputData1;\
  Input2 = pInputData2;\
  Output = pOutputData;\
  \
  /* Create and exectute filter */\
  Accessor< InputPixelType_1 > accInput1( Input1 );\
  Accessor< InputPixelType_2 > accInput2( Input2 );\
  KERNEL_NAME filter( Iter, accInput1, accInput2 );\
  filter.execute();\
  \
  /* get results*/\
  pOutputData = Output.getData();\
  \
  /* memory cleanup*/\
  free( pInputData1 );\
  free( pInputData2 );\
  free( pOutputData );\
  \
  return 0;\
}\

