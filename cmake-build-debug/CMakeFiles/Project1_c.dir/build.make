# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project1_c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Project1_c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Project1_c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project1_c.dir/flags.make

CMakeFiles/Project1_c.dir/main.c.obj: CMakeFiles/Project1_c.dir/flags.make
CMakeFiles/Project1_c.dir/main.c.obj: ../main.c
CMakeFiles/Project1_c.dir/main.c.obj: CMakeFiles/Project1_c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project1_c.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Project1_c.dir/main.c.obj -MF CMakeFiles\Project1_c.dir\main.c.obj.d -o CMakeFiles\Project1_c.dir\main.c.obj -c C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\main.c

CMakeFiles/Project1_c.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project1_c.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\main.c > CMakeFiles\Project1_c.dir\main.c.i

CMakeFiles/Project1_c.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project1_c.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\main.c -o CMakeFiles\Project1_c.dir\main.c.s

# Object files for target Project1_c
Project1_c_OBJECTS = \
"CMakeFiles/Project1_c.dir/main.c.obj"

# External object files for target Project1_c
Project1_c_EXTERNAL_OBJECTS =

Project1_c.exe: CMakeFiles/Project1_c.dir/main.c.obj
Project1_c.exe: CMakeFiles/Project1_c.dir/build.make
Project1_c.exe: CMakeFiles/Project1_c.dir/linklibs.rsp
Project1_c.exe: CMakeFiles/Project1_c.dir/objects1.rsp
Project1_c.exe: CMakeFiles/Project1_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Project1_c.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Project1_c.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project1_c.dir/build: Project1_c.exe
.PHONY : CMakeFiles/Project1_c.dir/build

CMakeFiles/Project1_c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Project1_c.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Project1_c.dir/clean

CMakeFiles/Project1_c.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug C:\Users\Ale\CLionProjects\Managing_Financial_Data_Project1_C\cmake-build-debug\CMakeFiles\Project1_c.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project1_c.dir/depend

