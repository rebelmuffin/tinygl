cmake_minimum_required(VERSION 3.0)
project(tinygl)
add_compile_options(-O3)
set(OpenGL_GL_PREFERENCE "GLVND")

set(CMAKE_CXX_STANDARD 14)

include_directories(include src)
add_executable(tinygl main.cpp src/Shader.cpp src/Shader.h src/Texture.cpp src/Texture.h src/Camera.cpp src/Camera.h src/Cube.cpp src/Cube.h)

add_library(GLAD "thirdparty/glad.c")
add_library(stb_image "thirdparty/stb_image.cpp")

find_package(OpenGL REQUIRED)

find_package(glm REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(glfw3 3.3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

target_link_libraries(tinygl glfw OpenGL::GL GLAD stb_image)
