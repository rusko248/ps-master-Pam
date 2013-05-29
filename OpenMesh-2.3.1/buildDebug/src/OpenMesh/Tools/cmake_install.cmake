# Install script for directory: /Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools

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
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Tools/libOpenMeshToolsd.2.3.dylib"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Tools/libOpenMeshToolsd.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenMesh/libOpenMeshToolsd.2.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenMesh/libOpenMeshToolsd.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/OpenMesh/libOpenMeshToolsd.2.3.dylib"
        -change "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Core/libOpenMeshCored.2.3.dylib" "/usr/local/lib/OpenMesh/libOpenMeshCored.2.3.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OpenMesh" TYPE FILE PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE RENAME "libOpenMeshToolsd.a" FILES "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/buildDebug/src/OpenMesh/Tools/./libOpenMeshToolsStaticd.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Decimater" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/BaseDecimaterT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/CollapseInfoT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/DecimaterT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/McDecimaterT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/MixedDecimaterT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModAspectRatioT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModBaseT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModEdgeLengthT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModHausdorffT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModIndependentSetsT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModNormalDeviationT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModNormalFlippingT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModProgMeshT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModQuadricT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModRoundnessT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/BaseDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/DecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/McDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/MixedDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModAspectRatioT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModEdgeLengthT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModHausdorffT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModProgMeshT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModQuadricT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Dualizer" TYPE FILE FILES "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Dualizer/meshDualT.hh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Kernel_OSG" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/ArrayKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/AttribKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/bindT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/color_cast.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/PropertyKernel.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/PropertyT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/Traits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/TriMesh_OSGArrayKernelT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Kernel_OSG/VectorAdapter.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Smoother" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Smoother/LaplaceSmootherT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Smoother/smooth_mesh.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Smoother/SmootherT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/BaseDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/DecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/McDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/MixedDecimaterT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModAspectRatioT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModEdgeLengthT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModHausdorffT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModProgMeshT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Decimater/ModQuadricT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Adaptive/Composite" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeTraits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RuleInterfaceT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RulesT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/Traits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RulesT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Uniform" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/CatmullClarkT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/CompositeLoopT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/CompositeSqrt3T.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/LongestEdgeT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/LoopT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/ModifiedButterFlyT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/Sqrt3InterpolatingSubdividerLabsikGreinerT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/Sqrt3T.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/SubdividerT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/CatmullClarkT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Uniform/Composite" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeTraits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeT.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Utils" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/Config.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/conio.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/GLConstAsString.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/Gnuplot.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/HeapT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/MeshCheckerT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/NumLimitsT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/StripifierT.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/TestingFramework.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/Timer.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/Gnuplot.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/MeshCheckerT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/StripifierT.cc"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/Utils/getopt.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/VDPM" TYPE FILE FILES
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/MeshTraits.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/StreamingDef.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VFront.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VHierarchy.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VHierarchyNode.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VHierarchyNodeIndex.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VHierarchyWindow.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/ViewingParameters.hh"
    "/Users/Pam/Documents/12-13 Stanford/03 Spring/CS248/HW/hw_animation/OpenMesh-2.3.1/src/OpenMesh/Tools/VDPM/VFront.cc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

