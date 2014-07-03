#pragma once

class TopologicalErosion
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

  static void _RunUInt8(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

