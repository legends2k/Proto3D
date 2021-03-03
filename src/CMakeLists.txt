# TODO: generate config.h with path to a “data” directory, allowing binary to
# be placed and launched anywhere freely. Refer:
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/comms.html
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_executable(${PROJECT_NAME} "main.cpp")

# Confirm strictly to C++17; needs CMake 3.8+
# https://cliutils.gitlab.io/modern-cmake/chapters/features/cpp11.html
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# https://foonathan.net/2018/10/cmake-warnings/
if (CMAKE_COMPILER_IS_GNUCXX OR
    MINGW OR
    (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic
    -pedantic-errors -fno-rtti -fno-exceptions -Wno-missing-field-initializers
    -Wcast-align -Wconversion -Wcast-qual -Wdouble-promotion -Wno-div-by-zero)
elseif (MSVC)
  # exceptions are off by default
  target_compile_options(${PROJECT_NAME} PRIVATE /W3 /GR-)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wvector-operation-performance -Wlogical-op")
endif ()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)

# When to use PRIVATE, PUBLIC and INTERFACE?
# https://stackoverflow.com/q/26037954/183120
target_include_directories(${PROJECT_NAME} PRIVATE ".")
# Use SYSTEM to avoid warnings on extenal headers
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY} GLAD)

# generate compile_commands.json needed for tools like RTags, Clang parser, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
