#ifndef _MANDELBROT_HANDLER_DEFINES_H_
#define _MANDELBROT_HANDLER_DEFINES_H_

#define LAUNCH_HANDLER_SCALAR( _HandlerName, _OutputImage, _StrideOutput, _x0, _y0, _dx, _dy, _count ) \
_HandlerName( _OutputImage->Data, _OutputImage->GetWidth(), _OutputImage->GetHeight(), _StrideOutput, _x0, _y0, _dx, _dy, _count );

#define LAUNCH_HANDLER_VECTORIZED( _HandlerName, _OutputImage, _StrideOutput, _x0, _y0, _dx, _dy, _count ) \
        LAUNCH_HANDLER_SCALAR( _HandlerName, _OutputImage, _StrideOutput, _x0, _y0, _dx, _dy, _count )

#endif // _MANDELBROT_HANDLER_DEFINES_H_
