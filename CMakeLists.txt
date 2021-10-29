cmake_minimum_required(VERSION 2.8)

# give a name to the project
project(RayTracer)
set(CMAKE_VERBOSE_MAKEFILE ON)

# exec
add_executable(RayTracer
    src/ray_tracer.cpp
    src/Object.cpp
    src/Scene.cpp
)

# Compile options
target_compile_features(RayTracer PRIVATE cxx_std_17)

find_library(MY_LIB NAMES libg3x.6c.64b++.so PATHS /usr/lib)
target_link_libraries(RayTracer ${MY_LIB} libGL.so)

find_library(GLUT_LIB NAMES libglut.so PATHS /usr/lib/x86_64-linux-gnu)
target_link_libraries(RayTracer ${GLUT_LIB} libGL.so)

find_library(GLU_LIB NAMES libGLU.so PATHS /usr/lib/x86_64-linux-gnu)
target_link_libraries(RayTracer ${GLU_LIB} libGL.so)

find_library(GL_LIB NAMES libGL.so PATHS /usr/lib/x86_64-linux-gnu)
target_link_libraries(RayTracer ${GL_LIB} libGL.so)

if(MSVC)
  target_compile_options(RayTracer PRIVATE /W4 /WX ${libG3X} -L/usr/lib -lm -lGL -lGLU -lglut)
else()
  target_compile_options(RayTracer PRIVATE -Wall -Wextra -Werror -Wshadow ${libG3X} -L/usr/lib -lm -lGL -lGLU -lglut)
endif()

