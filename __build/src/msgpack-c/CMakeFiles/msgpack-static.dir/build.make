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

# Include any dependencies generated for this target.
include src/msgpack-c/CMakeFiles/msgpack-static.dir/depend.make

# Include the progress variables for this target.
include src/msgpack-c/CMakeFiles/msgpack-static.dir/progress.make

# Include the compile flags for this target's objects.
include src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o: src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make
src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o: ../src/msgpack-c/src/unpack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgpack-static.dir/src/unpack.c.o   -c /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/unpack.c

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgpack-static.dir/src/unpack.c.i"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/unpack.c > CMakeFiles/msgpack-static.dir/src/unpack.c.i

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgpack-static.dir/src/unpack.c.s"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/unpack.c -o CMakeFiles/msgpack-static.dir/src/unpack.c.s

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.requires:

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.provides: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.requires
	$(MAKE) -f src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.provides.build
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.provides

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.provides.build: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o


src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o: src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make
src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o: ../src/msgpack-c/src/objectc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgpack-static.dir/src/objectc.c.o   -c /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/objectc.c

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgpack-static.dir/src/objectc.c.i"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/objectc.c > CMakeFiles/msgpack-static.dir/src/objectc.c.i

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgpack-static.dir/src/objectc.c.s"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/objectc.c -o CMakeFiles/msgpack-static.dir/src/objectc.c.s

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.requires:

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.provides: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.requires
	$(MAKE) -f src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.provides.build
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.provides

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.provides.build: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o


src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o: src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make
src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o: ../src/msgpack-c/src/version.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgpack-static.dir/src/version.c.o   -c /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/version.c

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgpack-static.dir/src/version.c.i"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/version.c > CMakeFiles/msgpack-static.dir/src/version.c.i

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgpack-static.dir/src/version.c.s"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/version.c -o CMakeFiles/msgpack-static.dir/src/version.c.s

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.requires:

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.provides: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.requires
	$(MAKE) -f src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.provides.build
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.provides

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.provides.build: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o


src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o: src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make
src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o: ../src/msgpack-c/src/vrefbuffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o   -c /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/vrefbuffer.c

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.i"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/vrefbuffer.c > CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.i

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.s"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/vrefbuffer.c -o CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.s

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.requires:

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.provides: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.requires
	$(MAKE) -f src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.provides.build
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.provides

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.provides.build: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o


src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o: src/msgpack-c/CMakeFiles/msgpack-static.dir/flags.make
src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o: ../src/msgpack-c/src/zone.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgpack-static.dir/src/zone.c.o   -c /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/zone.c

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgpack-static.dir/src/zone.c.i"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/zone.c > CMakeFiles/msgpack-static.dir/src/zone.c.i

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgpack-static.dir/src/zone.c.s"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c/src/zone.c -o CMakeFiles/msgpack-static.dir/src/zone.c.s

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.requires:

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.provides: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.requires
	$(MAKE) -f src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.provides.build
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.provides

src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.provides.build: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o


# Object files for target msgpack-static
msgpack__static_OBJECTS = \
"CMakeFiles/msgpack-static.dir/src/unpack.c.o" \
"CMakeFiles/msgpack-static.dir/src/objectc.c.o" \
"CMakeFiles/msgpack-static.dir/src/version.c.o" \
"CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o" \
"CMakeFiles/msgpack-static.dir/src/zone.c.o"

# External object files for target msgpack-static
msgpack__static_EXTERNAL_OBJECTS =

src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/build.make
src/msgpack-c/libmsgpack.a: src/msgpack-c/CMakeFiles/msgpack-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xunto/Programming/freeminer/km-freeminer/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libmsgpack.a"
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && $(CMAKE_COMMAND) -P CMakeFiles/msgpack-static.dir/cmake_clean_target.cmake
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msgpack-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/msgpack-c/CMakeFiles/msgpack-static.dir/build: src/msgpack-c/libmsgpack.a

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/build

src/msgpack-c/CMakeFiles/msgpack-static.dir/requires: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/unpack.c.o.requires
src/msgpack-c/CMakeFiles/msgpack-static.dir/requires: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/objectc.c.o.requires
src/msgpack-c/CMakeFiles/msgpack-static.dir/requires: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/version.c.o.requires
src/msgpack-c/CMakeFiles/msgpack-static.dir/requires: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/vrefbuffer.c.o.requires
src/msgpack-c/CMakeFiles/msgpack-static.dir/requires: src/msgpack-c/CMakeFiles/msgpack-static.dir/src/zone.c.o.requires

.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/requires

src/msgpack-c/CMakeFiles/msgpack-static.dir/clean:
	cd /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c && $(CMAKE_COMMAND) -P CMakeFiles/msgpack-static.dir/cmake_clean.cmake
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/clean

src/msgpack-c/CMakeFiles/msgpack-static.dir/depend:
	cd /home/xunto/Programming/freeminer/km-freeminer/__build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xunto/Programming/freeminer/km-freeminer /home/xunto/Programming/freeminer/km-freeminer/src/msgpack-c /home/xunto/Programming/freeminer/km-freeminer/__build /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c /home/xunto/Programming/freeminer/km-freeminer/__build/src/msgpack-c/CMakeFiles/msgpack-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/msgpack-c/CMakeFiles/msgpack-static.dir/depend
