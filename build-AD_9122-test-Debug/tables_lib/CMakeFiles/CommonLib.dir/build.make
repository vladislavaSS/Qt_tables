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

# Include any dependencies generated for this target.
include tables_lib/CMakeFiles/CommonLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tables_lib/CMakeFiles/CommonLib.dir/compiler_depend.make

# Include the progress variables for this target.
include tables_lib/CMakeFiles/CommonLib.dir/progress.make

# Include the compile flags for this target's objects.
include tables_lib/CMakeFiles/CommonLib.dir/flags.make

tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/flags.make
tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o: tables_lib/CommonLib_autogen/mocs_compilation.cpp
tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o -MF CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib/CommonLib_autogen/mocs_compilation.cpp

tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.i"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib/CommonLib_autogen/mocs_compilation.cpp > CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.i

tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.s"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib/CommonLib_autogen/mocs_compilation.cpp -o CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.s

tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/flags.make
tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/buttons.cpp
tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o -MF CMakeFiles/CommonLib.dir/buttons.cpp.o.d -o CMakeFiles/CommonLib.dir/buttons.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/buttons.cpp

tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommonLib.dir/buttons.cpp.i"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/buttons.cpp > CMakeFiles/CommonLib.dir/buttons.cpp.i

tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommonLib.dir/buttons.cpp.s"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/buttons.cpp -o CMakeFiles/CommonLib.dir/buttons.cpp.s

tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/flags.make
tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/transform.cpp
tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o -MF CMakeFiles/CommonLib.dir/transform.cpp.o.d -o CMakeFiles/CommonLib.dir/transform.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/transform.cpp

tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommonLib.dir/transform.cpp.i"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/transform.cpp > CMakeFiles/CommonLib.dir/transform.cpp.i

tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommonLib.dir/transform.cpp.s"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/transform.cpp -o CMakeFiles/CommonLib.dir/transform.cpp.s

tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/flags.make
tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/сreate.cpp
tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o: tables_lib/CMakeFiles/CommonLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o -MF CMakeFiles/CommonLib.dir/сreate.cpp.o.d -o CMakeFiles/CommonLib.dir/сreate.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/сreate.cpp

tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommonLib.dir/сreate.cpp.i"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/сreate.cpp > CMakeFiles/CommonLib.dir/сreate.cpp.i

tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommonLib.dir/сreate.cpp.s"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && /usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib/сreate.cpp -o CMakeFiles/CommonLib.dir/сreate.cpp.s

# Object files for target CommonLib
CommonLib_OBJECTS = \
"CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/CommonLib.dir/buttons.cpp.o" \
"CMakeFiles/CommonLib.dir/transform.cpp.o" \
"CMakeFiles/CommonLib.dir/сreate.cpp.o"

# External object files for target CommonLib
CommonLib_EXTERNAL_OBJECTS =

tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/CommonLib_autogen/mocs_compilation.cpp.o
tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/buttons.cpp.o
tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/transform.cpp.o
tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/сreate.cpp.o
tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/build.make
tables_lib/libCommonLib.a: tables_lib/CMakeFiles/CommonLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libCommonLib.a"
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && $(CMAKE_COMMAND) -P CMakeFiles/CommonLib.dir/cmake_clean_target.cmake
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CommonLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tables_lib/CMakeFiles/CommonLib.dir/build: tables_lib/libCommonLib.a
.PHONY : tables_lib/CMakeFiles/CommonLib.dir/build

tables_lib/CMakeFiles/CommonLib.dir/clean:
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib && $(CMAKE_COMMAND) -P CMakeFiles/CommonLib.dir/cmake_clean.cmake
.PHONY : tables_lib/CMakeFiles/CommonLib.dir/clean

tables_lib/CMakeFiles/CommonLib.dir/depend:
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vadislava/qtprojects/qt_git/Qt_tables/AD_9122 /home/vadislava/qtprojects/qt_git/Qt_tables/tables_lib /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib /home/vadislava/qtprojects/qt_git/Qt_tables/build-AD_9122-test-Debug/tables_lib/CMakeFiles/CommonLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tables_lib/CMakeFiles/CommonLib.dir/depend

