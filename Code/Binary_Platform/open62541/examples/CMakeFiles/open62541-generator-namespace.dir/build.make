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

# Utility rule file for open62541-generator-namespace.

# Include the progress variables for this target.
include CMakeFiles/open62541-generator-namespace.dir/progress.make

CMakeFiles/open62541-generator-namespace: src_generated/ua_namespace0.c
CMakeFiles/open62541-generator-namespace: src_generated/ua_namespace0.h


src_generated/ua_namespace0.c: ../tools/schema/Opc.Ua.NodeSet2.Minimal.xml
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/nodeset_compiler.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/nodes.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/nodeset.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/datatypes.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/backend_open62541.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/backend_open62541_nodes.py
src_generated/ua_namespace0.c: ../tools/nodeset_compiler/backend_open62541_datatypes.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating src_generated/ua_namespace0.c, src_generated/ua_namespace0.h"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/nodeset_compiler/nodeset_compiler.py --generate-ns0 --internal-headers --max-string-length=0 --ignore /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/nodeset_compiler/NodeID_NS0_Base.txt --xml /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/Opc.Ua.NodeSet2.Minimal.xml /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_namespace0

src_generated/ua_namespace0.h: src_generated/ua_namespace0.c
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_namespace0.h

open62541-generator-namespace: CMakeFiles/open62541-generator-namespace
open62541-generator-namespace: src_generated/ua_namespace0.c
open62541-generator-namespace: src_generated/ua_namespace0.h
open62541-generator-namespace: CMakeFiles/open62541-generator-namespace.dir/build.make

.PHONY : open62541-generator-namespace

# Rule to build all files generated by this target.
CMakeFiles/open62541-generator-namespace.dir/build: open62541-generator-namespace

.PHONY : CMakeFiles/open62541-generator-namespace.dir/build

CMakeFiles/open62541-generator-namespace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open62541-generator-namespace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open62541-generator-namespace.dir/clean

CMakeFiles/open62541-generator-namespace.dir/depend:
	cd /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-generator-namespace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open62541-generator-namespace.dir/depend
