#pragma once

#include <memory>

template < typename PixelType, const int ciWidth, const int ciHeight >
class Image
{
public:

  enum
  {
    Width  = ciWidth,
    Height = ciHeight
  };


  PixelType Data[ Height ][ Width ];


  inline static std::shared_ptr< Image > Create()   { return std::make_shared< Image >(); }

  inline static int GetWidth()    { return Width; }
  inline static int GetHeight()   { return Height; }
};


#define MAKE_IMAGE_TYPE(__Name, __PixelType, __Width, __Height) \
  typedef Image< __PixelType, __Width, __Height >   __Name; \
  typedef std::shared_ptr< __Name >   __Name##Ptr;


#define CREATE_IMAGE(__ImageType, __VarName) \
  __ImageType##Ptr __VarName = __ImageType::Create();



