# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maxime/Documents/OpenGL/RayTracerCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maxime/Documents/OpenGL/RayTracerCpp/build

# Include any dependencies generated for this target.
include CMakeFiles/RayTracer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracer.dir/flags.make

CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o: ../src/ray_tracer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxime/Documents/OpenGL/RayTracerCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o"
	/usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o -c /home/maxime/Documents/OpenGL/RayTracerCpp/src/ray_tracer.cpp

CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.i"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxime/Documents/OpenGL/RayTracerCpp/src/ray_tracer.cpp > CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.i

CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.s"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxime/Documents/OpenGL/RayTracerCpp/src/ray_tracer.cpp -o CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.s

CMakeFiles/RayTracer.dir/src/Object.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/Object.cpp.o: ../src/Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxime/Documents/OpenGL/RayTracerCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RayTracer.dir/src/Object.cpp.o"
	/usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/src/Object.cpp.o -c /home/maxime/Documents/OpenGL/RayTracerCpp/src/Object.cpp

CMakeFiles/RayTracer.dir/src/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/Object.cpp.i"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxime/Documents/OpenGL/RayTracerCpp/src/Object.cpp > CMakeFiles/RayTracer.dir/src/Object.cpp.i

CMakeFiles/RayTracer.dir/src/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/Object.cpp.s"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxime/Documents/OpenGL/RayTracerCpp/src/Object.cpp -o CMakeFiles/RayTracer.dir/src/Object.cpp.s

CMakeFiles/RayTracer.dir/src/Scene.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/Scene.cpp.o: ../src/Scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxime/Documents/OpenGL/RayTracerCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RayTracer.dir/src/Scene.cpp.o"
	/usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/src/Scene.cpp.o -c /home/maxime/Documents/OpenGL/RayTracerCpp/src/Scene.cpp

CMakeFiles/RayTracer.dir/src/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/Scene.cpp.i"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxime/Documents/OpenGL/RayTracerCpp/src/Scene.cpp > CMakeFiles/RayTracer.dir/src/Scene.cpp.i

CMakeFiles/RayTracer.dir/src/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/Scene.cpp.s"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxime/Documents/OpenGL/RayTracerCpp/src/Scene.cpp -o CMakeFiles/RayTracer.dir/src/Scene.cpp.s

# Object files for target RayTracer
RayTracer_OBJECTS = \
"CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o" \
"CMakeFiles/RayTracer.dir/src/Object.cpp.o" \
"CMakeFiles/RayTracer.dir/src/Scene.cpp.o"

# External object files for target RayTracer
RayTracer_EXTERNAL_OBJECTS =

RayTracer: CMakeFiles/RayTracer.dir/src/ray_tracer.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/Object.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/Scene.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/build.make
RayTracer: /usr/local/lib/libg3x.6c.64b++.so
RayTracer: /usr/lib/x86_64-linux-gnu/libglut.so
RayTracer: /usr/lib/x86_64-linux-gnu/libglut.so
RayTracer: /usr/lib/x86_64-linux-gnu/libGLU.so
RayTracer: /usr/lib/x86_64-linux-gnu/libglut.so
RayTracer: /usr/lib/x86_64-linux-gnu/libGLU.so
RayTracer: CMakeFiles/RayTracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxime/Documents/OpenGL/RayTracerCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable RayTracer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RayTracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracer.dir/build: RayTracer

.PHONY : CMakeFiles/RayTracer.dir/build

CMakeFiles/RayTracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayTracer.dir/clean

CMakeFiles/RayTracer.dir/depend:
	cd /home/maxime/Documents/OpenGL/RayTracerCpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxime/Documents/OpenGL/RayTracerCpp /home/maxime/Documents/OpenGL/RayTracerCpp /home/maxime/Documents/OpenGL/RayTracerCpp/build /home/maxime/Documents/OpenGL/RayTracerCpp/build /home/maxime/Documents/OpenGL/RayTracerCpp/build/CMakeFiles/RayTracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayTracer.dir/depend
