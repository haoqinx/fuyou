# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/hqin/fuyou/fuyou

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hqin/fuyou/fuyou

# Include any dependencies generated for this target.
include CMakeFiles/servertest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/servertest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/servertest.dir/flags.make

CMakeFiles/servertest.dir/Channel.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Channel.cpp.o: Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/servertest.dir/Channel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Channel.cpp.o -c /home/hqin/fuyou/fuyou/Channel.cpp

CMakeFiles/servertest.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Channel.cpp > CMakeFiles/servertest.dir/Channel.cpp.i

CMakeFiles/servertest.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Channel.cpp -o CMakeFiles/servertest.dir/Channel.cpp.s

CMakeFiles/servertest.dir/Channel.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Channel.cpp.o.requires

CMakeFiles/servertest.dir/Channel.cpp.o.provides: CMakeFiles/servertest.dir/Channel.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Channel.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Channel.cpp.o.provides

CMakeFiles/servertest.dir/Channel.cpp.o.provides.build: CMakeFiles/servertest.dir/Channel.cpp.o


CMakeFiles/servertest.dir/Epoll.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Epoll.cpp.o: Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/servertest.dir/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Epoll.cpp.o -c /home/hqin/fuyou/fuyou/Epoll.cpp

CMakeFiles/servertest.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Epoll.cpp > CMakeFiles/servertest.dir/Epoll.cpp.i

CMakeFiles/servertest.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Epoll.cpp -o CMakeFiles/servertest.dir/Epoll.cpp.s

CMakeFiles/servertest.dir/Epoll.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Epoll.cpp.o.requires

CMakeFiles/servertest.dir/Epoll.cpp.o.provides: CMakeFiles/servertest.dir/Epoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Epoll.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Epoll.cpp.o.provides

CMakeFiles/servertest.dir/Epoll.cpp.o.provides.build: CMakeFiles/servertest.dir/Epoll.cpp.o


CMakeFiles/servertest.dir/EventLoop.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/EventLoop.cpp.o: EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/servertest.dir/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/EventLoop.cpp.o -c /home/hqin/fuyou/fuyou/EventLoop.cpp

CMakeFiles/servertest.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/EventLoop.cpp > CMakeFiles/servertest.dir/EventLoop.cpp.i

CMakeFiles/servertest.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/EventLoop.cpp -o CMakeFiles/servertest.dir/EventLoop.cpp.s

CMakeFiles/servertest.dir/EventLoop.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/EventLoop.cpp.o.requires

CMakeFiles/servertest.dir/EventLoop.cpp.o.provides: CMakeFiles/servertest.dir/EventLoop.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/EventLoop.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/EventLoop.cpp.o.provides

CMakeFiles/servertest.dir/EventLoop.cpp.o.provides.build: CMakeFiles/servertest.dir/EventLoop.cpp.o


CMakeFiles/servertest.dir/Timer.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Timer.cpp.o: Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/servertest.dir/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Timer.cpp.o -c /home/hqin/fuyou/fuyou/Timer.cpp

CMakeFiles/servertest.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Timer.cpp > CMakeFiles/servertest.dir/Timer.cpp.i

CMakeFiles/servertest.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Timer.cpp -o CMakeFiles/servertest.dir/Timer.cpp.s

CMakeFiles/servertest.dir/Timer.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Timer.cpp.o.requires

CMakeFiles/servertest.dir/Timer.cpp.o.provides: CMakeFiles/servertest.dir/Timer.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Timer.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Timer.cpp.o.provides

CMakeFiles/servertest.dir/Timer.cpp.o.provides.build: CMakeFiles/servertest.dir/Timer.cpp.o


CMakeFiles/servertest.dir/Util.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Util.cpp.o: Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/servertest.dir/Util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Util.cpp.o -c /home/hqin/fuyou/fuyou/Util.cpp

CMakeFiles/servertest.dir/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Util.cpp > CMakeFiles/servertest.dir/Util.cpp.i

CMakeFiles/servertest.dir/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Util.cpp -o CMakeFiles/servertest.dir/Util.cpp.s

CMakeFiles/servertest.dir/Util.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Util.cpp.o.requires

CMakeFiles/servertest.dir/Util.cpp.o.provides: CMakeFiles/servertest.dir/Util.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Util.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Util.cpp.o.provides

CMakeFiles/servertest.dir/Util.cpp.o.provides.build: CMakeFiles/servertest.dir/Util.cpp.o


CMakeFiles/servertest.dir/EventLoopThread.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/EventLoopThread.cpp.o: EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/servertest.dir/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/EventLoopThread.cpp.o -c /home/hqin/fuyou/fuyou/EventLoopThread.cpp

CMakeFiles/servertest.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/EventLoopThread.cpp > CMakeFiles/servertest.dir/EventLoopThread.cpp.i

CMakeFiles/servertest.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/EventLoopThread.cpp -o CMakeFiles/servertest.dir/EventLoopThread.cpp.s

CMakeFiles/servertest.dir/EventLoopThread.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/EventLoopThread.cpp.o.requires

CMakeFiles/servertest.dir/EventLoopThread.cpp.o.provides: CMakeFiles/servertest.dir/EventLoopThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/EventLoopThread.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/EventLoopThread.cpp.o.provides

CMakeFiles/servertest.dir/EventLoopThread.cpp.o.provides.build: CMakeFiles/servertest.dir/EventLoopThread.cpp.o


CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o: EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o -c /home/hqin/fuyou/fuyou/EventLoopThreadPool.cpp

CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/EventLoopThreadPool.cpp > CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.i

CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/EventLoopThreadPool.cpp -o CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.s

CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.requires

CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.provides: CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.provides

CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.provides.build: CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o


CMakeFiles/servertest.dir/Server.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Server.cpp.o: Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/servertest.dir/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Server.cpp.o -c /home/hqin/fuyou/fuyou/Server.cpp

CMakeFiles/servertest.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Server.cpp > CMakeFiles/servertest.dir/Server.cpp.i

CMakeFiles/servertest.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Server.cpp -o CMakeFiles/servertest.dir/Server.cpp.s

CMakeFiles/servertest.dir/Server.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Server.cpp.o.requires

CMakeFiles/servertest.dir/Server.cpp.o.provides: CMakeFiles/servertest.dir/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Server.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Server.cpp.o.provides

CMakeFiles/servertest.dir/Server.cpp.o.provides.build: CMakeFiles/servertest.dir/Server.cpp.o


CMakeFiles/servertest.dir/Main.cpp.o: CMakeFiles/servertest.dir/flags.make
CMakeFiles/servertest.dir/Main.cpp.o: Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/servertest.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servertest.dir/Main.cpp.o -c /home/hqin/fuyou/fuyou/Main.cpp

CMakeFiles/servertest.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servertest.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hqin/fuyou/fuyou/Main.cpp > CMakeFiles/servertest.dir/Main.cpp.i

CMakeFiles/servertest.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servertest.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hqin/fuyou/fuyou/Main.cpp -o CMakeFiles/servertest.dir/Main.cpp.s

CMakeFiles/servertest.dir/Main.cpp.o.requires:

.PHONY : CMakeFiles/servertest.dir/Main.cpp.o.requires

CMakeFiles/servertest.dir/Main.cpp.o.provides: CMakeFiles/servertest.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/servertest.dir/build.make CMakeFiles/servertest.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/servertest.dir/Main.cpp.o.provides

CMakeFiles/servertest.dir/Main.cpp.o.provides.build: CMakeFiles/servertest.dir/Main.cpp.o


# Object files for target servertest
servertest_OBJECTS = \
"CMakeFiles/servertest.dir/Channel.cpp.o" \
"CMakeFiles/servertest.dir/Epoll.cpp.o" \
"CMakeFiles/servertest.dir/EventLoop.cpp.o" \
"CMakeFiles/servertest.dir/Timer.cpp.o" \
"CMakeFiles/servertest.dir/Util.cpp.o" \
"CMakeFiles/servertest.dir/EventLoopThread.cpp.o" \
"CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o" \
"CMakeFiles/servertest.dir/Server.cpp.o" \
"CMakeFiles/servertest.dir/Main.cpp.o"

# External object files for target servertest
servertest_EXTERNAL_OBJECTS =

servertest: CMakeFiles/servertest.dir/Channel.cpp.o
servertest: CMakeFiles/servertest.dir/Epoll.cpp.o
servertest: CMakeFiles/servertest.dir/EventLoop.cpp.o
servertest: CMakeFiles/servertest.dir/Timer.cpp.o
servertest: CMakeFiles/servertest.dir/Util.cpp.o
servertest: CMakeFiles/servertest.dir/EventLoopThread.cpp.o
servertest: CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o
servertest: CMakeFiles/servertest.dir/Server.cpp.o
servertest: CMakeFiles/servertest.dir/Main.cpp.o
servertest: CMakeFiles/servertest.dir/build.make
servertest: base/libfuyou_base.a
servertest: CMakeFiles/servertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hqin/fuyou/fuyou/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable servertest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/servertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/servertest.dir/build: servertest

.PHONY : CMakeFiles/servertest.dir/build

CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Channel.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Epoll.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/EventLoop.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Timer.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Util.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/EventLoopThread.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/EventLoopThreadPool.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Server.cpp.o.requires
CMakeFiles/servertest.dir/requires: CMakeFiles/servertest.dir/Main.cpp.o.requires

.PHONY : CMakeFiles/servertest.dir/requires

CMakeFiles/servertest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/servertest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/servertest.dir/clean

CMakeFiles/servertest.dir/depend:
	cd /home/hqin/fuyou/fuyou && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hqin/fuyou/fuyou /home/hqin/fuyou/fuyou /home/hqin/fuyou/fuyou /home/hqin/fuyou/fuyou /home/hqin/fuyou/fuyou/CMakeFiles/servertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/servertest.dir/depend

