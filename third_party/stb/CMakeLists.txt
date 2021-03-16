project(stb)

add_library(${PROJECT_NAME} "src/stb.c")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
