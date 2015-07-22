#ifndef _MIN_MAX_DETECTOR_H_
#define _MIN_MAX_DETECTOR_H_

class MinMaxDetector
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

#endif // _MIN_MAX_DETECTOR_H_
