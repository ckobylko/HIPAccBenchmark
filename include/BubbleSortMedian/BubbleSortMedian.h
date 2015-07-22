#ifndef _BUBBLE_SORT_MEDIAN_H_
#define _BUBBLE_SORT_MEDIAN_H_

class BubbleSortMedian
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

#endif // _BUBBLE_SORT_MEDIAN_H_