# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vadislava/qtprojects/qt_git/Qt_tables/AD_9122

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug

# Utility rule file for AD_9122_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/AD_9122_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AD_9122_autogen.dir/progress.make

CMakeFiles/AD_9122_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target AD_9122"
	/usr/bin/cmake -E cmake_autogen /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles/AD_9122_autogen.dir/AutogenInfo.json Debug

AD_9122_autogen: CMakeFiles/AD_9122_autogen
AD_9122_autogen: CMakeFiles/AD_9122_autogen.dir/build.make
.PHONY : AD_9122_autogen

# Rule to build all files generated by this target.
CMakeFiles/AD_9122_autogen.dir/build: AD_9122_autogen
.PHONY : CMakeFiles/AD_9122_autogen.dir/build

CMakeFiles/AD_9122_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AD_9122_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AD_9122_autogen.dir/clean

CMakeFiles/AD_9122_autogen.dir/depend:
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vadislava/qtprojects/qt_git/Qt_tables/AD_9122 /home/vadislava/qtprojects/qt_git/Qt_tables/AD_9122 /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles/AD_9122_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AD_9122_autogen.dir/depend

