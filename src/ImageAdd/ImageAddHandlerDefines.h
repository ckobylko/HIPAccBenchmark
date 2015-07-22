#ifndef _IMAGE_ADD_HANDLER_DEFINES_H_
#define _IMAGE_ADD_HANDLER_DEFINES_H_

#define LAUNCH_HANDLER_SCALAR( _HandlerName, _OutputImage, _InputImage1, _InputImage2, _StrideOutput ) \
_HandlerName( _OutputImage->Data, _OutputImage->GetWidth(), _OutputImage->GetHeight(), _StrideOutput, _InputImage1->Data, _InputImage2->Data );

#define LAUNCH_HANDLER_VECTORIZED( _HandlerName, _OutputImage, _InputImage1, _InputImage2, _StrideOutput, _StrideInput1, _StrideInput2 ) \
_HandlerName( _OutputImage->Data, _OutputImage->GetWidth(), _OutputImage->GetHeight(), _StrideOutput, \
              _InputImage1->Data, _StrideInput1, _InputImage2->Data, _StrideInput2 );

#endif // _IMAGE_ADD_HANDLER_DEFINES_H_
