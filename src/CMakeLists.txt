set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_executable(${PROJECT_NAME} "glad.c" "main.cpp")

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
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS} ".")

find_package(GLFW3 REQUIRED)
message(STATUS "GLFW included from ${GLFW3_INCLUDE_DIR}")

find_package(GLM REQUIRED)
message(STATUS "GLM included from ${GLM_INCLUDE_DIR}")

target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY})

# disable optimizations, enable macro debugging with GDB level 3
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
# CMake sets only NDEBUG for Release builds; DEBUG needs manual definition
# https://stackoverflow.com/q/8591762/183120
target_compile_definitions(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

# generate compile_commands.json needed for RTags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
