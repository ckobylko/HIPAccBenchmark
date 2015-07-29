#define OutputPixelType unsigned int8

export void MandelbrotUInt8SSE4_2(
  uniform OutputPixelType output[],
  uniform int width,
  uniform int height,
  uniform int stride,
  uniform float x0,
  uniform float y0,
  uniform float dx,
  uniform float dy,
  uniform int count) {
  for (uniform int y = 0; y < height; ++y) {
    foreach(x = 0 ... width) {
      float c_re = x * dx + x0;
      float c_im = y * dy + y0;

      float z_re = c_re, z_im = c_im;
      OutputPixelType out = 0;
      for (int i = 0; i < count; ++i) {
        if (z_re * z_re + z_im * z_im > 4.) {
          out = (unsigned int8)i;
          break;
        }
        float new_re = z_re*z_re - z_im*z_im;
        float new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
      }
      output[y*stride + x] = out;
    }
  }
}
