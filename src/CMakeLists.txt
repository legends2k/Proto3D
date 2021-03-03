# TODO: generate config.h with path to a “data” directory, allowing binary to
# be placed and launched anywhere freely
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_executable(${PROJECT_NAME} "main.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ".")

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
  ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY} GLAD)

# generate compile_commands.json needed for tools like RTags, Clang parser, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
