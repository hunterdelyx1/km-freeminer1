# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xunto/Programming/freeminer/km-freeminer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xunto/Programming/freeminer/km-freeminer/__build

# Utility rule file for GenerateVersion.

# Include the progress variables for this target.
include src/CMakeFiles/GenerateVersion.dir/progress.make

src/CMakeFiles/GenerateVersion:
	cd /home/xunto/Programming/freeminer/km-freeminer/src && /usr/bin/cmake -D GENERATE_VERSION_SOURCE_DIR=/home/xunto/Programming/freeminer/km-freeminer/src -D GENERATE_VERSION_BINARY_DIR=/home/xunto/Programming/freeminer/km-freeminer/__build/src -D VERSION_STRING=0.4.13.7 -D DEVELOPMENT_BUILD=FALSE -P /home/xunto/Programming/freeminer/km-freeminer/cmake/Modules/GenerateVersion.cmake

GenerateVersion: src/CMakeFiles/GenerateVersion
GenerateVersion: src/CMakeFiles/GenerateVersion.dir/build.make

.PHONY : GenerateVersion

# Rule to build all files generated by this target.
src/CMakeFiles/GenerateVersion.dir/build: GenerateVersion

.PHONY : src/CMakeFiles/GenerateVersion.dir/build

src/CMakeFiles/GenerateVersion.dir/clean:
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src && $(CMAKE_COMMAND) -P CMakeFiles/GenerateVersion.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/GenerateVersion.dir/clean

src/CMakeFiles/GenerateVersion.dir/depend:
	cd /home/xunto/Programming/freeminer/km-freeminer/__build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xunto/Programming/freeminer/km-freeminer /home/xunto/Programming/freeminer/km-freeminer/src /home/xunto/Programming/freeminer/km-freeminer/__build /home/xunto/Programming/freeminer/km-freeminer/__build/src /home/xunto/Programming/freeminer/km-freeminer/__build/src/CMakeFiles/GenerateVersion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/GenerateVersion.dir/depend
