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

# Include any dependencies generated for this target.
include CMakeFiles/open62541.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/open62541.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/open62541.dir/flags.make

# Object files for target open62541
open62541_OBJECTS =

# External object files for target open62541
open62541_EXTERNAL_OBJECTS = \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_types.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_types_encoding_binary.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src_generated/ua_types_generated.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src_generated/ua_transport_generated.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src_generated/ua_statuscodes.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_util.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_timer.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_connection.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/ua_securechannel.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_session.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_nodes.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server_ns0.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src_generated/ua_namespace0.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server_binary.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server_utils.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server_worker.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_server_discovery.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_securechannel_manager.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_session_manager.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_subscription.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_subscription_datachange.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_subscription_events.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_networkmessage.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_manager.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_ns0.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_view.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_call.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_session.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_attribute.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_discovery.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_subscription.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_securechannel.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_nodemanagement.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/server/ua_services_discovery_multicast.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_connect.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_connect_async.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_discovery.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_highlevel.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_subscriptions.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/src/client/ua_client_worker.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/deps/libc_time.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-object.dir/deps/pcg_basic.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_network_tcp.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_clock.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_log_stdout.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_accesscontrol_default.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_pki_certificate.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_nodestore_default.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_config_default.c.o" \
"/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541-plugins.dir/plugins/ua_securitypolicy_none.c.o"

bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_types.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_types_encoding_binary.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src_generated/ua_types_generated.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src_generated/ua_transport_generated.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src_generated/ua_statuscodes.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_util.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_timer.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_connection.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/ua_securechannel.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_session.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_nodes.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server_ns0.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src_generated/ua_namespace0.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server_binary.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server_utils.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server_worker.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_server_discovery.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_securechannel_manager.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_session_manager.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_subscription.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_subscription_datachange.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_subscription_events.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_networkmessage.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_manager.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/pubsub/ua_pubsub_ns0.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_view.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_call.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_session.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_attribute.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_discovery.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_subscription.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_securechannel.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_nodemanagement.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/server/ua_services_discovery_multicast.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_connect.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_connect_async.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_discovery.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_highlevel.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_subscriptions.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/src/client/ua_client_worker.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/deps/libc_time.c.o
bin/libopen62541.a: CMakeFiles/open62541-object.dir/deps/pcg_basic.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_network_tcp.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_clock.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_log_stdout.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_accesscontrol_default.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_pki_certificate.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_nodestore_default.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_config_default.c.o
bin/libopen62541.a: CMakeFiles/open62541-plugins.dir/plugins/ua_securitypolicy_none.c.o
bin/libopen62541.a: CMakeFiles/open62541.dir/build.make
bin/libopen62541.a: CMakeFiles/open62541.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking C static library bin/libopen62541.a"
	$(CMAKE_COMMAND) -P CMakeFiles/open62541.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/open62541.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/open62541.dir/build: bin/libopen62541.a

.PHONY : CMakeFiles/open62541.dir/build

CMakeFiles/open62541.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open62541.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open62541.dir/clean

CMakeFiles/open62541.dir/depend:
	cd /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541 /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541/examples/CMakeFiles/open62541.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open62541.dir/depend
