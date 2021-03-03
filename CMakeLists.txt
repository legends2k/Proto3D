cmake_minimum_required(VERSION 3.1)
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

# TODO: generate config.h with path to a “data” directory, allowing binary to
# be placed and launched anywhere freely
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_executable(${PROJECT_NAME} "src/glad.c" "src/main.cpp")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-std=c++17 -Wall -pedantic -Wno-missing-field-initializers \
-Wextra -Wcast-align -Wconversion -Wcast-qual \
-Wdouble-promotion -Wno-div-by-zero")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wvector-operation-performance -Wlogical-op")
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR} "src")
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY})

# generate compile_commands.json needed for tools like RTags, Clang parser, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
