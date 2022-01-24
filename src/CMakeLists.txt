add_executable(${PROJECT_NAME} util.cpp main.cpp)

# Confirm strictly to C++17; needs CMake 3.8+
# https://cliutils.gitlab.io/modern-cmake/chapters/features/cpp11.html
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

# https://foonathan.net/2018/10/cmake-warnings/
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU,AppleClang,Clang>:-Wall -Wextra -pedantic
  -pedantic-errors -fno-rtti -fno-exceptions -Wno-missing-field-initializers
  -Wcast-align -Wconversion -Wcast-qual -Wdouble-promotion -Wno-div-by-zero>
  $<$<CXX_COMPILER_ID:MSVC>:/W3 /GR->
  # enable macro debugging with GDB level 3
  $<$<AND:$<CXX_COMPILER_ID:GNU,AppleClang,Clang>,$<CONFIG:DEBUG>>:-ggdb3>
  $<$<CXX_COMPILER_ID:GNU>:-Wvector-operation-performance -Wlogical-op>)

find_package(glfw3 3 REQUIRED)
# GLM 0.9+ is required but GLM’s config script errors out upon giving version
find_package(glm REQUIRED)

# When to use PRIVATE, PUBLIC and INTERFACE?
# https://stackoverflow.com/q/26037954/183120
target_link_libraries(${PROJECT_NAME} PRIVATE
  GLAD stb ${CMAKE_DL_LIBS} glfw
  $<IF:$<TARGET_EXISTS:glm::glm>,glm::glm,glm>)
