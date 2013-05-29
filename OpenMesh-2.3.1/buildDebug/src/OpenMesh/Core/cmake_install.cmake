# Install script for directory: /Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OpenMesh" TYPE SHARED_LIBRARY FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/libOpenMeshCored.2.3.dylib"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/libOpenMeshCored.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenMesh/libOpenMeshCored.2.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenMesh/libOpenMeshCored.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/OpenMesh/libOpenMeshCored.2.3.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OpenMesh" TYPE FILE PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE RENAME "libOpenMeshCored.a" FILES "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/./libOpenMeshCoreStaticd.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Geometry" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/Config.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/LoopSchemeMaskT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/MathDefs.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/NormalConeT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/Plane3d.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/QuadricT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/VectorT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/VectorT_inc.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Geometry/NormalConeT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/BinaryHelper.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/IOInstances.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/IOManager.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/MeshIO.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/OFFFormat.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/OMFormat.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/Options.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_binary.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_binary_spec.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_rbo.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_store.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_types.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/StoreRestore.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/OMFormat.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/OMFormatT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_binary_vector_of_bool.inl"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_binary_vector_of_fundamentals.inl"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/SR_binary_vector_of_string.inl"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/importer" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/importer/BaseImporter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/importer/ImporterT.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/exporter" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/exporter/BaseExporter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/exporter/ExporterT.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/reader" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/BaseReader.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/OBJReader.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/OFFReader.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/OMReader.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/PLYReader.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/reader/STLReader.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/writer" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/BaseWriter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/OBJWriter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/OFFWriter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/OMWriter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/PLYWriter.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/IO/writer/STLWriter.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Mesh" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/ArrayItems.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/ArrayKernel.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/AttribKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/Attributes.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/BaseKernel.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/BaseMesh.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/Casts.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/CirculatorsT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/FinalMeshItemsT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/Handles.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/IteratorsT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/PolyConnectivity.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/PolyMeshT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/Status.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/Traits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/TriConnectivity.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/TriMeshT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/ArrayKernelT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/PolyMeshT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/TriMeshT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Mesh/gen" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/gen/circulators_header.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/gen/circulators_template.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/gen/footer.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/gen/iterators_header.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Mesh/gen/iterators_template.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/System" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/compiler.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/config.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/mostream.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/omstream.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/OpenMeshDLLMacros.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/System/config.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Utils" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/AutoPropertyHandleT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/BaseProperty.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/color_cast.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/Endian.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/GenProg.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/Noncopyable.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/Property.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/PropertyContainer.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/PropertyManager.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/RandomNumberGenerator.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/SingletonT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/vector_cast.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/vector_traits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Core/Utils/SingletonT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

