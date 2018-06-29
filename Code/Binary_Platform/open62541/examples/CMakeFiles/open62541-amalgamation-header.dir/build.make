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

# Utility rule file for open62541-amalgamation-header.

# Include the progress variables for this target.
include CMakeFiles/open62541-amalgamation-header.dir/progress.make

CMakeFiles/open62541-amalgamation-header: open62541.h


open62541.h: ../tools/amalgamate.py
open62541.h: src_generated/ua_config.h
open62541.h: ../deps/ms_stdint.h
open62541.h: ../include/ua_constants.h
open62541.h: src_generated/ua_statuscodes.h
open62541.h: src_generated/ua_nodeids.h
open62541.h: ../include/ua_types.h
open62541.h: src_generated/ua_types_generated.h
open62541.h: src_generated/ua_types_generated_handling.h
open62541.h: ../include/ua_server.h
open62541.h: ../include/ua_plugin_log.h
open62541.h: ../include/ua_plugin_network.h
open62541.h: ../include/ua_plugin_access_control.h
open62541.h: ../include/ua_plugin_pki.h
open62541.h: ../include/ua_plugin_securitypolicy.h
open62541.h: ../include/ua_server_pubsub.h
open62541.h: ../include/ua_plugin_pubsub.h
open62541.h: ../include/ua_plugin_nodestore.h
open62541.h: ../include/ua_server_config.h
open62541.h: ../include/ua_client_config.h
open62541.h: ../include/ua_client.h
open62541.h: ../include/ua_client_highlevel.h
open62541.h: ../include/ua_client_subscriptions.h
open62541.h: ../include/ua_client_highlevel_async.h
open62541.h: ../plugins/ua_network_tcp.h
open62541.h: ../plugins/ua_accesscontrol_default.h
open62541.h: ../plugins/ua_pki_certificate.h
open62541.h: ../plugins/ua_log_stdout.h
open62541.h: ../plugins/ua_nodestore_default.h
open62541.h: ../plugins/ua_config_default.h
open62541.h: ../plugins/ua_securitypolicy_none.h
open62541.h: ../plugins/ua_log_socket_error.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating open62541.h"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/amalgamate.py 0.3-rc1-235-gfd304ae /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/open62541.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_config.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/deps/ms_stdint.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_constants.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_statuscodes.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_nodeids.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_types.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_types_generated.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_types_generated_handling.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_server.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_log.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_network.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_access_control.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_pki.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_securitypolicy.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_server_pubsub.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_pubsub.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_plugin_nodestore.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_server_config.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_client_config.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_client.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_client_highlevel.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_client_subscriptions.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/include/ua_client_highlevel_async.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_network_tcp.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_accesscontrol_default.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_pki_certificate.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_log_stdout.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_nodestore_default.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_config_default.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_securitypolicy_none.h /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/plugins/ua_log_socket_error.h

src_generated/ua_statuscodes.h: ../tools/generate_statuscode_descriptions.py
src_generated/ua_statuscodes.h: ../tools/schema/StatusCode.csv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating src_generated/ua_statuscodes.h, src_generated/ua_statuscodes.c"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/generate_statuscode_descriptions.py /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/StatusCode.csv /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_statuscodes

src_generated/ua_statuscodes.c: src_generated/ua_statuscodes.h
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_statuscodes.c

src_generated/ua_nodeids.h: ../tools/generate_nodeid_header.py
src_generated/ua_nodeids.h: ../tools/schema/NodeIds.csv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating src_generated/ua_nodeids.h"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/generate_nodeid_header.py /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/NodeIds.csv /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_nodeids NS0

src_generated/ua_types_generated.c: ../tools/generate_datatypes.py
src_generated/ua_types_generated.c: ../tools/schema/NodeIds.csv
src_generated/ua_types_generated.c: ../tools/schema/Opc.Ua.Types.bsd
src_generated/ua_types_generated.c: ../tools/schema/datatypes_minimal.txt
src_generated/ua_types_generated.c: ../tools/schema/datatypes_method.txt
src_generated/ua_types_generated.c: ../tools/schema/datatypes_discovery.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating src_generated/ua_types_generated.c, src_generated/ua_types_generated.h, src_generated/ua_types_generated_handling.h, src_generated/ua_types_generated_encoding_binary.h"
	/usr/bin/python /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/generate_datatypes.py --type-csv=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/NodeIds.csv --selected-types=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/datatypes_minimal.txt --selected-types=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/datatypes_method.txt --selected-types=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/datatypes_discovery.txt --type-bsd=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/tools/schema/Opc.Ua.Types.bsd /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/src_generated/ua_types

src_generated/ua_types_generated.h: src_generated/ua_types_generated.c
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_types_generated.h

src_generated/ua_types_generated_handling.h: src_generated/ua_types_generated.c
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_types_generated_handling.h

src_generated/ua_types_generated_encoding_binary.h: src_generated/ua_types_generated.c
	@$(CMAKE_COMMAND) -E touch_nocreate src_generated/ua_types_generated_encoding_binary.h

open62541-amalgamation-header: CMakeFiles/open62541-amalgamation-header
open62541-amalgamation-header: open62541.h
open62541-amalgamation-header: src_generated/ua_statuscodes.h
open62541-amalgamation-header: src_generated/ua_statuscodes.c
open62541-amalgamation-header: src_generated/ua_nodeids.h
open62541-amalgamation-header: src_generated/ua_types_generated.c
open62541-amalgamation-header: src_generated/ua_types_generated.h
open62541-amalgamation-header: src_generated/ua_types_generated_handling.h
open62541-amalgamation-header: src_generated/ua_types_generated_encoding_binary.h
open62541-amalgamation-header: CMakeFiles/open62541-amalgamation-header.dir/build.make

.PHONY : open62541-amalgamation-header

# Rule to build all files generated by this target.
CMakeFiles/open62541-amalgamation-header.dir/build: open62541-amalgamation-header

.PHONY : CMakeFiles/open62541-amalgamation-header.dir/build

CMakeFiles/open62541-amalgamation-header.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open62541-amalgamation-header.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open62541-amalgamation-header.dir/clean

CMakeFiles/open62541-amalgamation-header.dir/depend:
	cd /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-amalgamation-header.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open62541-amalgamation-header.dir/depend
