# Install script for directory: /home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/lib/open62541/arch

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/posix/cmake_install.cmake")
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/win32/cmake_install.cmake")
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/arduino/cmake_install.cmake")
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/freertosLWIP/cmake_install.cmake")
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/vxworks/cmake_install.cmake")
  include("/home/cgtybsr/Desktop/MyThesis/Master-s-Thesis/open62541-arduino/build/lib/open62541/arch/eCos/cmake_install.cmake")

endif()

