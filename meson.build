project('Proto3D', ['cpp', 'c'],
        version: '1.0.0',
        meson_version : '>= 0.55',
        default_options: ['strip=true',
                          'b_ndebug=if-release',
                          'cpp_std=c++17' ])

glfw3 = dependency('glfw3', version : '>=3.3')
glm   = dependency('glm', version : '>=0.9.8')
gl    = dependency('gl', required: true)

incdir = include_directories('src')
sources = files(
  'src/main.cpp',
  'src/glad.c',
)

Proto3D = executable(
  'proto3d',
  sources,
  include_directories: incdir,
  dependencies : [ glfw3, glm, gl ],
)
