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
CMAKE_SOURCE_DIR = "/home/sean/Desktop/C++ Programs/PheremoneDesigns"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/sean/Desktop/C++ Programs/PheremoneDesigns"

# Include any dependencies generated for this target.
include CMakeFiles/PheremoneDesigns.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PheremoneDesigns.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PheremoneDesigns.dir/flags.make

CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o: CMakeFiles/PheremoneDesigns.dir/flags.make
CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o: source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sean/Desktop/C++ Programs/PheremoneDesigns/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o -c "/home/sean/Desktop/C++ Programs/PheremoneDesigns/source/main.cpp"

CMakeFiles/PheremoneDesigns.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PheremoneDesigns.dir/source/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sean/Desktop/C++ Programs/PheremoneDesigns/source/main.cpp" > CMakeFiles/PheremoneDesigns.dir/source/main.cpp.i

CMakeFiles/PheremoneDesigns.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PheremoneDesigns.dir/source/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sean/Desktop/C++ Programs/PheremoneDesigns/source/main.cpp" -o CMakeFiles/PheremoneDesigns.dir/source/main.cpp.s

# Object files for target PheremoneDesigns
PheremoneDesigns_OBJECTS = \
"CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o"

# External object files for target PheremoneDesigns
PheremoneDesigns_EXTERNAL_OBJECTS =

PheremoneDesigns: CMakeFiles/PheremoneDesigns.dir/source/main.cpp.o
PheremoneDesigns: CMakeFiles/PheremoneDesigns.dir/build.make
PheremoneDesigns: libglad.a
PheremoneDesigns: /usr/local/lib/libopencv_gapi.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_highgui.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_ml.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_objdetect.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_photo.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_stitching.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_video.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_videoio.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_dnn.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_imgcodecs.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_calib3d.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_features2d.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_flann.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_imgproc.so.4.5.2
PheremoneDesigns: /usr/local/lib/libopencv_core.so.4.5.2
PheremoneDesigns: CMakeFiles/PheremoneDesigns.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/sean/Desktop/C++ Programs/PheremoneDesigns/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PheremoneDesigns"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PheremoneDesigns.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PheremoneDesigns.dir/build: PheremoneDesigns

.PHONY : CMakeFiles/PheremoneDesigns.dir/build

CMakeFiles/PheremoneDesigns.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PheremoneDesigns.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PheremoneDesigns.dir/clean

CMakeFiles/PheremoneDesigns.dir/depend:
	cd "/home/sean/Desktop/C++ Programs/PheremoneDesigns" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/sean/Desktop/C++ Programs/PheremoneDesigns" "/home/sean/Desktop/C++ Programs/PheremoneDesigns" "/home/sean/Desktop/C++ Programs/PheremoneDesigns" "/home/sean/Desktop/C++ Programs/PheremoneDesigns" "/home/sean/Desktop/C++ Programs/PheremoneDesigns/CMakeFiles/PheremoneDesigns.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PheremoneDesigns.dir/depend
