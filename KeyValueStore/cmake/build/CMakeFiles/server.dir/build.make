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
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.cc.o: ../../server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/server.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server.cc.o -c /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/server.cc

CMakeFiles/server.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/server.cc > CMakeFiles/server.dir/server.cc.i

CMakeFiles/server.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/server.cc -o CMakeFiles/server.dir/server.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.cc.o
server: CMakeFiles/server.dir/build.make
server: libhw_grpc_proto.a
server: libMyCache_.a
server: libstorage_.a
server: libconfigReader_.a
server: /home/avi/.local/lib/libgrpc++_reflection.a
server: /home/avi/.local/lib/libgrpc++.a
server: /home/avi/.local/lib/libprotobuf.a
server: /home/avi/.local/lib/libgrpc.a
server: /home/avi/.local/lib/libz.a
server: /home/avi/.local/lib/libcares.a
server: /home/avi/.local/lib/libaddress_sorting.a
server: /home/avi/.local/lib/libre2.a
server: /home/avi/.local/lib/libabsl_hash.a
server: /home/avi/.local/lib/libabsl_city.a
server: /home/avi/.local/lib/libabsl_wyhash.a
server: /home/avi/.local/lib/libabsl_raw_hash_set.a
server: /home/avi/.local/lib/libabsl_hashtablez_sampler.a
server: /home/avi/.local/lib/libabsl_exponential_biased.a
server: /home/avi/.local/lib/libabsl_statusor.a
server: /home/avi/.local/lib/libabsl_bad_variant_access.a
server: /home/avi/.local/lib/libgpr.a
server: /home/avi/.local/lib/libupb.a
server: /home/avi/.local/lib/libabsl_status.a
server: /home/avi/.local/lib/libabsl_cord.a
server: /home/avi/.local/lib/libabsl_str_format_internal.a
server: /home/avi/.local/lib/libabsl_synchronization.a
server: /home/avi/.local/lib/libabsl_stacktrace.a
server: /home/avi/.local/lib/libabsl_symbolize.a
server: /home/avi/.local/lib/libabsl_debugging_internal.a
server: /home/avi/.local/lib/libabsl_demangle_internal.a
server: /home/avi/.local/lib/libabsl_graphcycles_internal.a
server: /home/avi/.local/lib/libabsl_malloc_internal.a
server: /home/avi/.local/lib/libabsl_time.a
server: /home/avi/.local/lib/libabsl_strings.a
server: /home/avi/.local/lib/libabsl_throw_delegate.a
server: /home/avi/.local/lib/libabsl_strings_internal.a
server: /home/avi/.local/lib/libabsl_base.a
server: /home/avi/.local/lib/libabsl_spinlock_wait.a
server: /home/avi/.local/lib/libabsl_int128.a
server: /home/avi/.local/lib/libabsl_civil_time.a
server: /home/avi/.local/lib/libabsl_time_zone.a
server: /home/avi/.local/lib/libabsl_bad_optional_access.a
server: /home/avi/.local/lib/libabsl_raw_logging_internal.a
server: /home/avi/.local/lib/libabsl_log_severity.a
server: /home/avi/.local/lib/libssl.a
server: /home/avi/.local/lib/libcrypto.a
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

