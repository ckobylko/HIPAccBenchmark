#pragma once

class MinMaxDetector
{
private:

  static void _RunFloat(unsigned int uiKernelSize);

public:

  static void Run(unsigned int uiKernelSize);
};

