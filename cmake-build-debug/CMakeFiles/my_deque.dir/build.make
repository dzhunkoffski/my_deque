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
CMAKE_SOURCE_DIR = /home/dzhunkoff/my_deque

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dzhunkoff/my_deque/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/my_deque.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_deque.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_deque.dir/flags.make

CMakeFiles/my_deque.dir/main.cpp.o: CMakeFiles/my_deque.dir/flags.make
CMakeFiles/my_deque.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhunkoff/my_deque/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_deque.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_deque.dir/main.cpp.o -c /home/dzhunkoff/my_deque/main.cpp

CMakeFiles/my_deque.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_deque.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhunkoff/my_deque/main.cpp > CMakeFiles/my_deque.dir/main.cpp.i

CMakeFiles/my_deque.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_deque.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhunkoff/my_deque/main.cpp -o CMakeFiles/my_deque.dir/main.cpp.s

# Object files for target my_deque
my_deque_OBJECTS = \
"CMakeFiles/my_deque.dir/main.cpp.o"

# External object files for target my_deque
my_deque_EXTERNAL_OBJECTS =

my_deque: CMakeFiles/my_deque.dir/main.cpp.o
my_deque: CMakeFiles/my_deque.dir/build.make
my_deque: CMakeFiles/my_deque.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dzhunkoff/my_deque/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable my_deque"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_deque.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_deque.dir/build: my_deque

.PHONY : CMakeFiles/my_deque.dir/build

CMakeFiles/my_deque.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_deque.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_deque.dir/clean

CMakeFiles/my_deque.dir/depend:
	cd /home/dzhunkoff/my_deque/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dzhunkoff/my_deque /home/dzhunkoff/my_deque /home/dzhunkoff/my_deque/cmake-build-debug /home/dzhunkoff/my_deque/cmake-build-debug /home/dzhunkoff/my_deque/cmake-build-debug/CMakeFiles/my_deque.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_deque.dir/depend

