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
CMAKE_SOURCE_DIR = /home/sax/ros-dumbobot/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sax/ros-dumbobot/build

# Include any dependencies generated for this target.
include simple_navigation_goals/CMakeFiles/waypoint_nav.dir/depend.make

# Include the progress variables for this target.
include simple_navigation_goals/CMakeFiles/waypoint_nav.dir/progress.make

# Include the compile flags for this target's objects.
include simple_navigation_goals/CMakeFiles/waypoint_nav.dir/flags.make

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/flags.make
simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o: /home/sax/ros-dumbobot/src/simple_navigation_goals/src/waypoint_navigation_full.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sax/ros-dumbobot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o"
	cd /home/sax/ros-dumbobot/build/simple_navigation_goals && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o -c /home/sax/ros-dumbobot/src/simple_navigation_goals/src/waypoint_navigation_full.cpp

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.i"
	cd /home/sax/ros-dumbobot/build/simple_navigation_goals && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sax/ros-dumbobot/src/simple_navigation_goals/src/waypoint_navigation_full.cpp > CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.i

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.s"
	cd /home/sax/ros-dumbobot/build/simple_navigation_goals && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sax/ros-dumbobot/src/simple_navigation_goals/src/waypoint_navigation_full.cpp -o CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.s

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.requires:

.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.requires

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.provides: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.requires
	$(MAKE) -f simple_navigation_goals/CMakeFiles/waypoint_nav.dir/build.make simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.provides.build
.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.provides

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.provides.build: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o


# Object files for target waypoint_nav
waypoint_nav_OBJECTS = \
"CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o"

# External object files for target waypoint_nav
waypoint_nav_EXTERNAL_OBJECTS =

/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/build.make
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libroslib.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libtf.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libtf2_ros.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libactionlib.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libmessage_filters.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libroscpp.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libtf2.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/librosconsole.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/librostime.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /opt/ros/kinetic/lib/libcpp_common.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sax/ros-dumbobot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav"
	cd /home/sax/ros-dumbobot/build/simple_navigation_goals && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/waypoint_nav.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
simple_navigation_goals/CMakeFiles/waypoint_nav.dir/build: /home/sax/ros-dumbobot/devel/lib/simple_navigation_goals/waypoint_nav

.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/build

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/requires: simple_navigation_goals/CMakeFiles/waypoint_nav.dir/src/waypoint_navigation_full.cpp.o.requires

.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/requires

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/clean:
	cd /home/sax/ros-dumbobot/build/simple_navigation_goals && $(CMAKE_COMMAND) -P CMakeFiles/waypoint_nav.dir/cmake_clean.cmake
.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/clean

simple_navigation_goals/CMakeFiles/waypoint_nav.dir/depend:
	cd /home/sax/ros-dumbobot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sax/ros-dumbobot/src /home/sax/ros-dumbobot/src/simple_navigation_goals /home/sax/ros-dumbobot/build /home/sax/ros-dumbobot/build/simple_navigation_goals /home/sax/ros-dumbobot/build/simple_navigation_goals/CMakeFiles/waypoint_nav.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : simple_navigation_goals/CMakeFiles/waypoint_nav.dir/depend

