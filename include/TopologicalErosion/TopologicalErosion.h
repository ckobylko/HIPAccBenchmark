#ifndef _TOPOLOGICAL_EROSION_H_
#define _TOPOLOGICAL_EROSION_H_

class TopologicalErosion
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

#endif // _TOPOLOGICAL_EROSION_H_
