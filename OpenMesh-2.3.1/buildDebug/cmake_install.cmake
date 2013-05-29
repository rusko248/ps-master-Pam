# Install script for directory: /Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/cmake_install.cmake")
  INCLUDE("/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Tools/cmake_install.cmake")
  INCLUDE("/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/cmake_install.cmake")
  INCLUDE("/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/Unittests/cmake_install.cmake")
  INCLUDE("/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/Doc/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
