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
CMAKE_COMMAND = /home/avi/.local/bin/cmake

# The command to remove a file.
RM = /home/avi/.local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/hw_grpc_proto.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw_grpc_proto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw_grpc_proto.dir/flags.make

keyvaluestore.pb.cc: ../../keyvaluestore.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating keyvaluestore.pb.cc, keyvaluestore.pb.h, keyvaluestore.grpc.pb.cc, keyvaluestore.grpc.pb.h"
	/home/avi/.local/bin/protoc-3.17.3.0 --grpc_out /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build --cpp_out /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build -I /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore --plugin=protoc-gen-grpc="/home/avi/.local/bin/grpc_cpp_plugin" /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/keyvaluestore.proto

keyvaluestore.pb.h: keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate keyvaluestore.pb.h

keyvaluestore.grpc.pb.cc: keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate keyvaluestore.grpc.pb.cc

keyvaluestore.grpc.pb.h: keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate keyvaluestore.grpc.pb.h

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o: CMakeFiles/hw_grpc_proto.dir/flags.make
CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o: keyvaluestore.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o -c /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.grpc.pb.cc

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.grpc.pb.cc > CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.i

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.grpc.pb.cc -o CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.s

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o: CMakeFiles/hw_grpc_proto.dir/flags.make
CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o: keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o -c /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.pb.cc

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.pb.cc > CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.i

CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/keyvaluestore.pb.cc -o CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.s

# Object files for target hw_grpc_proto
hw_grpc_proto_OBJECTS = \
"CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o" \
"CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o"

# External object files for target hw_grpc_proto
hw_grpc_proto_EXTERNAL_OBJECTS =

libhw_grpc_proto.a: CMakeFiles/hw_grpc_proto.dir/keyvaluestore.grpc.pb.cc.o
libhw_grpc_proto.a: CMakeFiles/hw_grpc_proto.dir/keyvaluestore.pb.cc.o
libhw_grpc_proto.a: CMakeFiles/hw_grpc_proto.dir/build.make
libhw_grpc_proto.a: CMakeFiles/hw_grpc_proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libhw_grpc_proto.a"
	$(CMAKE_COMMAND) -P CMakeFiles/hw_grpc_proto.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw_grpc_proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw_grpc_proto.dir/build: libhw_grpc_proto.a

.PHONY : CMakeFiles/hw_grpc_proto.dir/build

CMakeFiles/hw_grpc_proto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw_grpc_proto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw_grpc_proto.dir/clean

CMakeFiles/hw_grpc_proto.dir/depend: keyvaluestore.pb.cc
CMakeFiles/hw_grpc_proto.dir/depend: keyvaluestore.pb.h
CMakeFiles/hw_grpc_proto.dir/depend: keyvaluestore.grpc.pb.cc
CMakeFiles/hw_grpc_proto.dir/depend: keyvaluestore.grpc.pb.h
	cd /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles/hw_grpc_proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw_grpc_proto.dir/depend

