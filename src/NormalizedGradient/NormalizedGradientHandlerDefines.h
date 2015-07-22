#ifndef _NORMALIZED_GRADIENT_HANDLER_DEFINES_H_
#define _NORMALIZED_GRADIENT_HANDLER_DEFINES_H_

#define LAUNCH_HANDLER_SCALAR( _HandlerName, _OutputImage1, _OutputImage2, _InputImage1, _InputImage2, _StrideOutput ) \
_HandlerName( _OutputImage1->Data, _OutputImage1->GetWidth(), _OutputImage1->GetHeight(), _StrideOutput, _OutputImage2->Data, _InputImage1->Data, _InputImage2->Data );

#define LAUNCH_HANDLER_VECTORIZED( _HandlerName, _OutputImage1, _OutputImage2, _InputImage1, _InputImage2, _StrideOutput, _StrideInput1, _StrideInput2 ) \
_HandlerName( _OutputImage1->Data, _OutputImage1->GetWidth(), _OutputImage1->GetHeight(), _StrideOutput, _OutputImage2->Data, \
              _InputImage1->Data, _StrideInput1, _InputImage2->Data, _StrideInput2 );

#endif // _NORMALIZED_GRADIENT_HANDLER_DEFINES_H_
