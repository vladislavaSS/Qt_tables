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
CMAKE_SOURCE_DIR = /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug

# Include any dependencies generated for this target.
include CMakeFiles/HMC_1035.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HMC_1035.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HMC_1035.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HMC_1035.dir/flags.make

CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o: HMC_1035_autogen/mocs_compilation.cpp
CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o -MF CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/HMC_1035_autogen/mocs_compilation.cpp

CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/HMC_1035_autogen/mocs_compilation.cpp > CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.i

CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/HMC_1035_autogen/mocs_compilation.cpp -o CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.s

CMakeFiles/HMC_1035.dir/main.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/main.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/main.cpp
CMakeFiles/HMC_1035.dir/main.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HMC_1035.dir/main.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/main.cpp.o -MF CMakeFiles/HMC_1035.dir/main.cpp.o.d -o CMakeFiles/HMC_1035.dir/main.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/main.cpp

CMakeFiles/HMC_1035.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/main.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/main.cpp > CMakeFiles/HMC_1035.dir/main.cpp.i

CMakeFiles/HMC_1035.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/main.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/main.cpp -o CMakeFiles/HMC_1035.dir/main.cpp.s

CMakeFiles/HMC_1035.dir/mainwindow.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/mainwindow.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/mainwindow.cpp
CMakeFiles/HMC_1035.dir/mainwindow.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HMC_1035.dir/mainwindow.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/mainwindow.cpp.o -MF CMakeFiles/HMC_1035.dir/mainwindow.cpp.o.d -o CMakeFiles/HMC_1035.dir/mainwindow.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/mainwindow.cpp

CMakeFiles/HMC_1035.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/mainwindow.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/mainwindow.cpp > CMakeFiles/HMC_1035.dir/mainwindow.cpp.i

CMakeFiles/HMC_1035.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/mainwindow.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/mainwindow.cpp -o CMakeFiles/HMC_1035.dir/mainwindow.cpp.s

CMakeFiles/HMC_1035.dir/data.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/data.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/data.cpp
CMakeFiles/HMC_1035.dir/data.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HMC_1035.dir/data.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/data.cpp.o -MF CMakeFiles/HMC_1035.dir/data.cpp.o.d -o CMakeFiles/HMC_1035.dir/data.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/data.cpp

CMakeFiles/HMC_1035.dir/data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/data.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/data.cpp > CMakeFiles/HMC_1035.dir/data.cpp.i

CMakeFiles/HMC_1035.dir/data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/data.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/data.cpp -o CMakeFiles/HMC_1035.dir/data.cpp.s

CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/HMC1035-widget.cpp
CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o -MF CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o.d -o CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/HMC1035-widget.cpp

CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/HMC1035-widget.cpp > CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.i

CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/HMC1035-widget.cpp -o CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.s

CMakeFiles/HMC_1035.dir/create.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/create.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/create.cpp
CMakeFiles/HMC_1035.dir/create.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/HMC_1035.dir/create.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/create.cpp.o -MF CMakeFiles/HMC_1035.dir/create.cpp.o.d -o CMakeFiles/HMC_1035.dir/create.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/create.cpp

CMakeFiles/HMC_1035.dir/create.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/create.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/create.cpp > CMakeFiles/HMC_1035.dir/create.cpp.i

CMakeFiles/HMC_1035.dir/create.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/create.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/create.cpp -o CMakeFiles/HMC_1035.dir/create.cpp.s

CMakeFiles/HMC_1035.dir/buttons.cpp.o: CMakeFiles/HMC_1035.dir/flags.make
CMakeFiles/HMC_1035.dir/buttons.cpp.o: /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/buttons.cpp
CMakeFiles/HMC_1035.dir/buttons.cpp.o: CMakeFiles/HMC_1035.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/HMC_1035.dir/buttons.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HMC_1035.dir/buttons.cpp.o -MF CMakeFiles/HMC_1035.dir/buttons.cpp.o.d -o CMakeFiles/HMC_1035.dir/buttons.cpp.o -c /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/buttons.cpp

CMakeFiles/HMC_1035.dir/buttons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HMC_1035.dir/buttons.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/buttons.cpp > CMakeFiles/HMC_1035.dir/buttons.cpp.i

CMakeFiles/HMC_1035.dir/buttons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HMC_1035.dir/buttons.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035/buttons.cpp -o CMakeFiles/HMC_1035.dir/buttons.cpp.s

# Object files for target HMC_1035
HMC_1035_OBJECTS = \
"CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/HMC_1035.dir/main.cpp.o" \
"CMakeFiles/HMC_1035.dir/mainwindow.cpp.o" \
"CMakeFiles/HMC_1035.dir/data.cpp.o" \
"CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o" \
"CMakeFiles/HMC_1035.dir/create.cpp.o" \
"CMakeFiles/HMC_1035.dir/buttons.cpp.o"

# External object files for target HMC_1035
HMC_1035_EXTERNAL_OBJECTS =

HMC_1035: CMakeFiles/HMC_1035.dir/HMC_1035_autogen/mocs_compilation.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/main.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/mainwindow.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/data.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/HMC1035-widget.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/create.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/buttons.cpp.o
HMC_1035: CMakeFiles/HMC_1035.dir/build.make
HMC_1035: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
HMC_1035: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
HMC_1035: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
HMC_1035: CMakeFiles/HMC_1035.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable HMC_1035"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HMC_1035.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HMC_1035.dir/build: HMC_1035
.PHONY : CMakeFiles/HMC_1035.dir/build

CMakeFiles/HMC_1035.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HMC_1035.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HMC_1035.dir/clean

CMakeFiles/HMC_1035.dir/depend:
	cd /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035 /home/vadislava/qtprojects/qt_git/Qt_tables/HMC_1035 /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug /home/vadislava/qtprojects/qt_git/Qt_tables/build-HMC_1035-test-Debug/CMakeFiles/HMC_1035.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HMC_1035.dir/depend

