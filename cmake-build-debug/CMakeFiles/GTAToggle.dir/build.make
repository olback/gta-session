# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = A:\Documents\GitHub\gta-session

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = A:\Documents\GitHub\gta-session\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GTAToggle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GTAToggle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GTAToggle.dir/flags.make

CMakeFiles/GTAToggle.dir/main.c.obj: CMakeFiles/GTAToggle.dir/flags.make
CMakeFiles/GTAToggle.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=A:\Documents\GitHub\gta-session\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/GTAToggle.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\GTAToggle.dir\main.c.obj   -c A:\Documents\GitHub\gta-session\main.c

CMakeFiles/GTAToggle.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GTAToggle.dir/main.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E A:\Documents\GitHub\gta-session\main.c > CMakeFiles\GTAToggle.dir\main.c.i

CMakeFiles/GTAToggle.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GTAToggle.dir/main.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S A:\Documents\GitHub\gta-session\main.c -o CMakeFiles\GTAToggle.dir\main.c.s

CMakeFiles/GTAToggle.dir/main.c.obj.requires:

.PHONY : CMakeFiles/GTAToggle.dir/main.c.obj.requires

CMakeFiles/GTAToggle.dir/main.c.obj.provides: CMakeFiles/GTAToggle.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\GTAToggle.dir\build.make CMakeFiles/GTAToggle.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/GTAToggle.dir/main.c.obj.provides

CMakeFiles/GTAToggle.dir/main.c.obj.provides.build: CMakeFiles/GTAToggle.dir/main.c.obj


# Object files for target GTAToggle
GTAToggle_OBJECTS = \
"CMakeFiles/GTAToggle.dir/main.c.obj"

# External object files for target GTAToggle
GTAToggle_EXTERNAL_OBJECTS =

GTAToggle.exe: CMakeFiles/GTAToggle.dir/main.c.obj
GTAToggle.exe: CMakeFiles/GTAToggle.dir/build.make
GTAToggle.exe: CMakeFiles/GTAToggle.dir/linklibs.rsp
GTAToggle.exe: CMakeFiles/GTAToggle.dir/objects1.rsp
GTAToggle.exe: CMakeFiles/GTAToggle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=A:\Documents\GitHub\gta-session\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable GTAToggle.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GTAToggle.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GTAToggle.dir/build: GTAToggle.exe

.PHONY : CMakeFiles/GTAToggle.dir/build

CMakeFiles/GTAToggle.dir/requires: CMakeFiles/GTAToggle.dir/main.c.obj.requires

.PHONY : CMakeFiles/GTAToggle.dir/requires

CMakeFiles/GTAToggle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GTAToggle.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GTAToggle.dir/clean

CMakeFiles/GTAToggle.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" A:\Documents\GitHub\gta-session A:\Documents\GitHub\gta-session A:\Documents\GitHub\gta-session\cmake-build-debug A:\Documents\GitHub\gta-session\cmake-build-debug A:\Documents\GitHub\gta-session\cmake-build-debug\CMakeFiles\GTAToggle.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GTAToggle.dir/depend

