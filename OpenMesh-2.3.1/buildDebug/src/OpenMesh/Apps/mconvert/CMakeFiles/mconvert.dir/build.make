# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = "/Applications/CMake 2.8-11.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-11.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-11.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug"

# Include any dependencies generated for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: ../src/OpenMesh/Apps/mconvert/mconvert.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o"
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mconvert.dir/mconvert.cc.o -c "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Apps/mconvert/mconvert.cc"

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mconvert.dir/mconvert.cc.i"
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Apps/mconvert/mconvert.cc" > CMakeFiles/mconvert.dir/mconvert.cc.i

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mconvert.dir/mconvert.cc.s"
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Apps/mconvert/mconvert.cc" -o CMakeFiles/mconvert.dir/mconvert.cc.s

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires:
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires
	$(MAKE) -f src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build.make src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides.build
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides.build: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o

# Object files for target mconvert
mconvert_OBJECTS = \
"CMakeFiles/mconvert.dir/mconvert.cc.o"

# External object files for target mconvert
mconvert_EXTERNAL_OBJECTS =

src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build.make
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Core/libOpenMeshCored.2.3.dylib
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Tools/libOpenMeshToolsd.2.3.dylib
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Core/libOpenMeshCored.2.3.dylib
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mconvert"
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mconvert.dir/link.txt --verbose=$(VERBOSE)
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && "/Applications/CMake 2.8-11.app/Contents/bin/cmake" -E copy_if_different /Users/Pam/Documents/12-13\ Stanford/03\ Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert/./mconvert /Users/Pam/Documents/12-13\ Stanford/03\ Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/Build/bin/mconvert

# Rule to build all files generated by this target.
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build: src/OpenMesh/Apps/mconvert/mconvert
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/requires: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/requires

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean:
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" && $(CMAKE_COMMAND) -P CMakeFiles/mconvert.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend:
	cd "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1" "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Apps/mconvert" "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug" "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert" "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend

