# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/97252/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/97252/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/97252/Desktop/DS_1_WET

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DS_1_WET.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DS_1_WET.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DS_1_WET.dir/flags.make

CMakeFiles/DS_1_WET.dir/main.cpp.o: CMakeFiles/DS_1_WET.dir/flags.make
CMakeFiles/DS_1_WET.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DS_1_WET.dir/main.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DS_1_WET.dir/main.cpp.o -c /cygdrive/c/Users/97252/Desktop/DS_1_WET/main.cpp

CMakeFiles/DS_1_WET.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DS_1_WET.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/97252/Desktop/DS_1_WET/main.cpp > CMakeFiles/DS_1_WET.dir/main.cpp.i

CMakeFiles/DS_1_WET.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DS_1_WET.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/97252/Desktop/DS_1_WET/main.cpp -o CMakeFiles/DS_1_WET.dir/main.cpp.s

# Object files for target DS_1_WET
DS_1_WET_OBJECTS = \
"CMakeFiles/DS_1_WET.dir/main.cpp.o"

# External object files for target DS_1_WET
DS_1_WET_EXTERNAL_OBJECTS =

DS_1_WET.exe: CMakeFiles/DS_1_WET.dir/main.cpp.o
DS_1_WET.exe: CMakeFiles/DS_1_WET.dir/build.make
DS_1_WET.exe: CMakeFiles/DS_1_WET.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DS_1_WET.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DS_1_WET.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DS_1_WET.dir/build: DS_1_WET.exe

.PHONY : CMakeFiles/DS_1_WET.dir/build

CMakeFiles/DS_1_WET.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DS_1_WET.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DS_1_WET.dir/clean

CMakeFiles/DS_1_WET.dir/depend:
	cd /cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/97252/Desktop/DS_1_WET /cygdrive/c/Users/97252/Desktop/DS_1_WET /cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug /cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug /cygdrive/c/Users/97252/Desktop/DS_1_WET/cmake-build-debug/CMakeFiles/DS_1_WET.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DS_1_WET.dir/depend
