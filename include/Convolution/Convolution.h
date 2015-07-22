#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

class Convolution
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

#endif // _CONVOLUTION_H_
