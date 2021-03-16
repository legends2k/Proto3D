# Refer
# https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects
# https://cliutils.gitlab.io/modern-cmake/chapters/intro/dodonot.html

cmake_minimum_required(VERSION 3.8)
project(Proto3D VERSION 1.0
                LANGUAGES CXX C)  # GLAD needs C

# Set a default build type if none was specified
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

add_subdirectory(third_party/GLAD)
add_subdirectory(third_party/stb)
add_subdirectory(src)
