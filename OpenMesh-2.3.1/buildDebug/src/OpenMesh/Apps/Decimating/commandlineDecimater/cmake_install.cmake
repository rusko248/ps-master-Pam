# Install script for directory: /Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Apps/Decimating/commandlineDecimater

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Apps/Decimating/commandlineDecimater/commandlineDecimater")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/commandlineDecimater" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/commandlineDecimater")
    EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/libOpenMeshCored.2.3.dylib" "/usr/local/lib/OpenMesh/libOpenMeshCored.2.3.dylib"
      -change "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Tools/libOpenMeshToolsd.2.3.dylib" "/usr/local/lib/OpenMesh/libOpenMeshToolsd.2.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/commandlineDecimater")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/commandlineDecimater")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

