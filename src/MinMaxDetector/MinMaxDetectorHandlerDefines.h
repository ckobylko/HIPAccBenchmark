#pragma once

#define LAUNCH_HANDLER_SCALAR( _HandlerName, _OutputImage, _InputImage, _StrideOutput, _Anchor ) \
_HandlerName( _OutputImage->Data, _OutputImage->GetWidth() - _Anchor * 2, _OutputImage->GetHeight() - _Anchor * 2, _StrideOutput, \
              _Anchor, _Anchor, _InputImage->Data, _Anchor, _Anchor, _Anchor );

#define LAUNCH_HANDLER_VECTORIZED( _HandlerName, _OutputImage, _InputImage, _StrideOutput, _StrideInput, _Anchor ) \
_HandlerName( _OutputImage->Data, _OutputImage->GetWidth() - _Anchor * 2, _OutputImage->GetHeight() - _Anchor * 2, _StrideOutput, \
              _Anchor, _Anchor, _InputImage->Data, _StrideInput, _Anchor, _Anchor, _Anchor );

