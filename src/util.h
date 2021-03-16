#ifndef __UTIL_H__
#define __UTIL_H__

#include "glad/glad.h"

#include <cstddef>

inline
size_t diff_or_err(long val,
                   long min,
                   long max,
                   size_t err)
{
  if ((val < min) || (val > max))
    return err;
  return static_cast<size_t>(val - min);
}

void gl_debug_logger(GLenum source, GLenum type, GLuint id, GLenum severity,
                     GLsizei /*length*/, const char *msg, const void *user_data);

#endif  // __UTIL_H__
