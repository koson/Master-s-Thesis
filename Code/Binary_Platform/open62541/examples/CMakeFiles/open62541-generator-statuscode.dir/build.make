# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples

# Utility rule file for open62541-generator-statuscode.

# Include the progress variables for this target.
include CMakeFiles/open62541-generator-statuscode.dir/progress.make

CMakeFiles/open62541-generator-statuscode: src_generated/ua_nodeids.h
CMakeFiles/open62541-generator-statuscode: src_generated/ua_statuscodes.h
CMakeFiles/open62541-generator-statuscode: src_generated/ua_statuscodes.c


src_generated/ua_nodeids.h: ../tools/generate_nodeid_header.py
src_generated/ua_nodeids.h: ../tools/schema/NodeIds.csv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating src_generated/ua_nodeids.h"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/generate_nodeid_header.py /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/NodeIds.csv /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_nodeids NS0

src_generated/ua_statuscodes.h: ../tools/generate_statuscode_descriptions.py
src_generated/ua_statuscodes.h: ../tools/schema/StatusCode.csv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating src_generated/ua_statuscodes.h, src_generated/ua_statuscodes.c"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/generate_statuscode_descriptions.py /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/StatusCode.csv /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_statuscodes

src_generated/ua_statuscodes.c: src_generated/ua_statuscodes.h
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_statuscodes.c

open62541-generator-statuscode: CMakeFiles/open62541-generator-statuscode
open62541-generator-statuscode: src_generated/ua_nodeids.h
open62541-generator-statuscode: src_generated/ua_statuscodes.h
open62541-generator-statuscode: src_generated/ua_statuscodes.c
open62541-generator-statuscode: CMakeFiles/open62541-generator-statuscode.dir/build.make

.PHONY : open62541-generator-statuscode

# Rule to build all files generated by this target.
CMakeFiles/open62541-generator-statuscode.dir/build: open62541-generator-statuscode

.PHONY : CMakeFiles/open62541-generator-statuscode.dir/build

CMakeFiles/open62541-generator-statuscode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open62541-generator-statuscode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open62541-generator-statuscode.dir/clean

CMakeFiles/open62541-generator-statuscode.dir/depend:
	cd /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-generator-statuscode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open62541-generator-statuscode.dir/depend
