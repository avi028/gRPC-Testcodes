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
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client.cc.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client.cc.o: ../../client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/client.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/client.cc.o -c /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/client.cc

CMakeFiles/client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/client.cc > CMakeFiles/client.dir/client.cc.i

CMakeFiles/client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/client.cc -o CMakeFiles/client.dir/client.cc.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.cc.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/client.cc.o
client: CMakeFiles/client.dir/build.make
client: libhw_grpc_proto.a
client: libMyCache_.a
client: libstorage_.a
client: libconfigReader_.a
client: /home/avi/.local/lib/libgrpc++_reflection.a
client: /home/avi/.local/lib/libgrpc++.a
client: /home/avi/.local/lib/libprotobuf.a
client: /home/avi/.local/lib/libgrpc.a
client: /home/avi/.local/lib/libz.a
client: /home/avi/.local/lib/libcares.a
client: /home/avi/.local/lib/libaddress_sorting.a
client: /home/avi/.local/lib/libre2.a
client: /home/avi/.local/lib/libabsl_hash.a
client: /home/avi/.local/lib/libabsl_city.a
client: /home/avi/.local/lib/libabsl_wyhash.a
client: /home/avi/.local/lib/libabsl_raw_hash_set.a
client: /home/avi/.local/lib/libabsl_hashtablez_sampler.a
client: /home/avi/.local/lib/libabsl_exponential_biased.a
client: /home/avi/.local/lib/libabsl_statusor.a
client: /home/avi/.local/lib/libabsl_bad_variant_access.a
client: /home/avi/.local/lib/libgpr.a
client: /home/avi/.local/lib/libupb.a
client: /home/avi/.local/lib/libabsl_status.a
client: /home/avi/.local/lib/libabsl_cord.a
client: /home/avi/.local/lib/libabsl_str_format_internal.a
client: /home/avi/.local/lib/libabsl_synchronization.a
client: /home/avi/.local/lib/libabsl_stacktrace.a
client: /home/avi/.local/lib/libabsl_symbolize.a
client: /home/avi/.local/lib/libabsl_debugging_internal.a
client: /home/avi/.local/lib/libabsl_demangle_internal.a
client: /home/avi/.local/lib/libabsl_graphcycles_internal.a
client: /home/avi/.local/lib/libabsl_malloc_internal.a
client: /home/avi/.local/lib/libabsl_time.a
client: /home/avi/.local/lib/libabsl_strings.a
client: /home/avi/.local/lib/libabsl_throw_delegate.a
client: /home/avi/.local/lib/libabsl_strings_internal.a
client: /home/avi/.local/lib/libabsl_base.a
client: /home/avi/.local/lib/libabsl_spinlock_wait.a
client: /home/avi/.local/lib/libabsl_int128.a
client: /home/avi/.local/lib/libabsl_civil_time.a
client: /home/avi/.local/lib/libabsl_time_zone.a
client: /home/avi/.local/lib/libabsl_bad_optional_access.a
client: /home/avi/.local/lib/libabsl_raw_logging_internal.a
client: /home/avi/.local/lib/libabsl_log_severity.a
client: /home/avi/.local/lib/libssl.a
client: /home/avi/.local/lib/libcrypto.a
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build /home/avi/IITB/cs744/Assignment4/grpc/examples/cpp/KeyValueStore/cmake/build/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

