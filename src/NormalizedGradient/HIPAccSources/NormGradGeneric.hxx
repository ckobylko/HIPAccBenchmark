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
  Accessor<InputPixelType_1>  &Input1;\
  Accessor<InputPixelType_2>  &Input2;\
  Accessor<OutputPixelType>   &Output2;\
  \
public:\
  KERNEL_NAME( IterationSpace<OutputPixelType> &iter, Accessor<OutputPixelType> &output2, \
               Accessor<InputPixelType_1> &input1,    Accessor<InputPixelType_2> &input2 ) : Kernel(iter), Input1(input1), Input2(input2), Output2(output2)\
  {\
    add_accessor( &Input1 );\
    add_accessor( &Input2 );\
    add_accessor( &Output2 );\
}\
  \
  void kernel() {\
    float TVal1 = (float) Input1(0, 0); \
    float TVal2 = (float) Input2(0, 0); \
    \
    float fNorm = std::sqrt( TVal1 * TVal1  +  TVal2 * TVal2 ) + static_cast<float>(1.0e-12); \
    \
    output()  = static_cast< OutputPixelType >( TVal1 / fNorm );\
    Output2() = static_cast< OutputPixelType >( TVal2 / fNorm );\
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
  OutputPixelType   *pOutputData1 = (OutputPixelType*)  calloc( cszMemorySize, sizeof(OutputPixelType)  );\
  OutputPixelType   *pOutputData2 = (OutputPixelType*)  calloc( cszMemorySize, sizeof(OutputPixelType)  );\
  \
  /* Create input and output images*/ \
  Image< InputPixelType_1 >           Input1( ciImageWidth, ciImageHeight );\
  Image< InputPixelType_2 >           Input2( ciImageWidth, ciImageHeight );\
  Image< OutputPixelType  >           Output1( ciImageWidth, ciImageHeight );\
  Image< OutputPixelType  >           Output2( ciImageWidth, ciImageHeight );\
  IterationSpace< OutputPixelType >   Iter( Output1, ciImageWidth, ciImageHeight );\
  \
  /* Set inputs*/ \
  Input1  = pInputData1;\
  Input2  = pInputData2;\
  Output1 = pOutputData1;\
  Output2 = pOutputData2;\
  \
  /* Create and exectute filter */\
  Accessor< InputPixelType_1 > accInput1( Input1 );\
  Accessor< InputPixelType_2 > accInput2( Input2 );\
  Accessor< OutputPixelType >  accOutput2( Output2 );\
  KERNEL_NAME filter( Iter, accOutput2, accInput1, accInput2 );\
  filter.execute();\
  \
  /* get results*/\
  pOutputData1 = Output1.data();\
  pOutputData2 = Output2.data();\
  \
  /* memory cleanup*/\
  free( pInputData1 );\
  free( pInputData2 );\
  free( pOutputData1 );\
  free( pOutputData2 );\
  \
  return 0;\
}\

