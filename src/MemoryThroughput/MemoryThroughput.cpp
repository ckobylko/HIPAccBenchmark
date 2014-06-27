#include "stdafx.h"
#include "../../include/MemoryThroughput/MemoryThroughput.h"
#include "TestRead.h"
#include "TestWrite.h"
#include <malloc.h>
#include <stdexcept>
using namespace MemoryThroughputTest;


template <typename PixelType>
PixelType* _AllocateImage(size_t szWidth, size_t szHeight)
{
  void *pvData = _aligned_malloc( szWidth * szHeight * sizeof(PixelType), static_cast< size_t >( 32 ) );

  if (pvData == nullptr)
  {
    throw std::runtime_error( "Aligned allocation failed" );
  }

  return reinterpret_cast< PixelType* >( pvData );
}


void MemoryThroughput::Run()
{
  const size_t        cszWidth    = static_cast< size_t >( 8192 );
  const size_t        cszHeight   = static_cast< size_t >( 4096 );
  const unsigned int  cuiIters    = 100;

  printf( "\n  Running \"MemoryThroughput\":\n" );

  TestRead    ReadTester ( cuiIters, cszWidth, cszHeight );
  TestWrite   WriteTester( cuiIters, cszWidth, cszHeight );

  // Allocate memory
  unsigned char *pucData  = _AllocateImage< unsigned char >( cszWidth, cszHeight );
  float         *pfData   = _AllocateImage< float         >( cszWidth, cszHeight );


  // Test read
  printf("\n    Running \"TestRead\":\n");

  ReadTester.RunUInt8( pucData, false );
  ReadTester.RunUInt8( pucData, true  );

  ReadTester.RunFloat( pfData, false );
  ReadTester.RunFloat( pfData, true  );


  // Test write
  printf("\n    Running \"TestWrite\":\n");

  WriteTester.RunUInt8( pucData, false );
  WriteTester.RunUInt8( pucData, true  );

  WriteTester.RunFloat( pfData, false );
  WriteTester.RunFloat( pfData, true  );


  // Free memory
  _aligned_free( pucData );
  _aligned_free( pfData  );

  printf("\n");
}

