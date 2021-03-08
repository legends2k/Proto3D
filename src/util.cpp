#include "util.h"

#include <type_traits>
#include <sstream>
#include <iostream>

void gl_debug_logger(GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei /*length*/,
                     const char *msg,
                     const void *user_data)
{
  std::stringstream ss;
  ss << "GLError 0x"
     << std::hex << id << std::dec
     << ": "
     << msg <<
    " [source=";

  const char *sources[] = {
    "API",
    "WINDOW_SYSTEM",
    "SHADER_COMPILER",
    "THIRD_PARTY",
    "APPLICATION",
    "OTHER",
    "UNDEFINED"
  };
  constexpr size_t sources_len = std::extent<decltype(sources)>::value - 1;
  size_t index = diff_or_err(source,
                             GL_DEBUG_SOURCE_API_KHR,
                             GL_DEBUG_SOURCE_OTHER_KHR,
                             sources_len);
  ss << sources[index];
  if (sources_len == index)
  {
    ss << " (" << source << ")";
  }

  const char *types[] = {
    "ERROR",
    "DEPRECATED_BEHAVIOR",
    "UNDEFINED_BEHAVIOR",
    "PORTABILITY",
    "PERFORMANCE",
    "OTHER",
    "UNDEFINED"
  };
  constexpr size_t types_len = std::extent<decltype(types)>::value - 1;
  index = diff_or_err(type,
                      GL_DEBUG_TYPE_ERROR_KHR,
                      GL_DEBUG_TYPE_OTHER_KHR,
                      types_len);
  ss << " type=" << types[index];
  if (types_len == index)
  {
    ss << " (" << type << ")";
  }

  const char *severities[] = {
    "HIGH",
    "MEDIUM",
    "LOW",
    "UNKNOWN"
  };
  constexpr size_t severities_len = std::extent<decltype(severities)>::value - 1;
  // as per the extension, HIGH is the base (smaller) value
  index = diff_or_err(severity,
                      GL_DEBUG_SEVERITY_HIGH_KHR,
                      GL_DEBUG_SEVERITY_LOW_KHR,
                      severities_len);
  ss << " severity=" << severities[index];
  if (severities_len == index)
  {
    ss << " (" << severity << ")";
  }
  ss << "]";

  const auto log = ss.str();
  FILE *out_file = reinterpret_cast<FILE*>(const_cast<void*>(user_data));
  fprintf(out_file, "%s\n", log.c_str());

  if (severity == GL_DEBUG_SEVERITY_HIGH_KHR)
    std::cerr << "High severity GL error logged\n";
}
