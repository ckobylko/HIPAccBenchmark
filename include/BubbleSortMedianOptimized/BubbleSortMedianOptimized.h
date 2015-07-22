#ifndef _BUBBLE_SORT_MEDIAN_OPTIMIZED_H_
#define _BUBBLE_SORT_MEDIAN_OPTIMIZED_H_

class BubbleSortMedianOptimized
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

#endif // _BUBBLE_SORT_MEDIAN_OPTIMIZED_H_
