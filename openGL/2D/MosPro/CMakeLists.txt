# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_CXX_DIR ${PROJECT_SOURCE_DIR}/src)


# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/glfw-2.7.9/include/
	external/glm-0.9.4.0/
    external/glew-1.9.0/include/
    external/
    include/physics
    include/lib
    /include/graphics
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_279
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


add_library(box2D "${PROJECT_CXX_DIR}/box2D.cpp")

#Graphics libraries

add_library(bufferObject "${PROJECT_CXX_DIR}/graphics/bufferObject.cpp")
add_library(circleGeometry2D "${PROJECT_CXX_DIR}/graphics/circleGeometry2D.cpp")
add_library(geometry2D "${PROJECT_CXX_DIR}/graphics/geometry2D.cpp")
add_library(glEngine2D "${PROJECT_CXX_DIR}/graphics/glEngine2D.cpp")
add_library(material2D "${PROJECT_CXX_DIR}/graphics/material2D.cpp")
add_library(shape2D "${PROJECT_CXX_DIR}/graphics/shape2D.cpp")
add_library(temporaryBufferObject "${PROJECT_CXX_DIR}/graphics/temporaryBufferObject.cpp")
add_library(wallGeometry2D "${PROJECT_CXX_DIR}/graphics/wallGeometry2D.cpp")


#Lib libraries
add_library(debugGL "${PROJECT_CXX_DIR}/lib/debugGL.cpp")

#Other libraries
add_library(glmIO "${PROJECT_CXX_DIR}/glmIO.cpp")


#Physics libraries
add_library(BSPNode2D "${PROJECT_CXX_DIR}/physics/BSPNode2D.cpp")
add_library(collision2D "${PROJECT_CXX_DIR}/physics/collision2D.cpp")
add_library(collisionDetector2D "${PROJECT_CXX_DIR}/physics/collisionDetector2D.cpp")
add_library(contactGroup "${PROJECT_CXX_DIR}/physics/contactGroup.cpp")
add_library(edge "${PROJECT_CXX_DIR}/physics/edge.cpp")
add_library(forceGenerator2D "${PROJECT_CXX_DIR}/physics/forceGenerator2D.cpp")
add_library(gravity2D "${PROJECT_CXX_DIR}/physics/gravity2D.cpp")
add_library(immovableBody2D "${PROJECT_CXX_DIR}/physics/immovableBody2D.cpp")
add_library(movableBody2D "${PROJECT_CXX_DIR}/physics/movableBody2D.cpp")
add_library(physicsEngine2D "${PROJECT_CXX_DIR}/physics/physicsEngine2D.cpp")
add_library(potentialCollision2D "${PROJECT_CXX_DIR}/physics/potentialCollision2D.cpp")
add_library(rigidBody2D "${PROJECT_CXX_DIR}/physics/rigidBody2D.cpp")
add_library(spring "${PROJECT_CXX_DIR}/physics/spring.cpp")
add_library(minkowskiPoint2D "${PROJECT_CXX_DIR}/physics/minkowskiPoint2D.cpp")
add_library(mbStateMap "${PROJECT_CXX_DIR}/physics/mbStateMap.cpp")
add_library(mbState "${PROJECT_CXX_DIR}/physics/mbState.cpp")

#Executable
add_executable(mospro 
	src/main.cpp
    external/common/shader.cpp
    external/common/shader.hpp
    "${CMAKE_SOURCE_DIR}/ColorFragmentShader.fragmentshader"
    "${CMAKE_SOURCE_DIR}/TransformVertexShader.vertexshader"
)
target_link_libraries(mospro
	${ALL_LIBS}
    box2D
    circleGeometry2D
    physicsEngine2D
    glEngine2D
    material2D
    rigidBody2D
    bufferObject
    collision2D
    movableBody2D
    wallGeometry2D
    collisionDetector2D
    minkowskiPoint2D
    immovableBody2D
    temporaryBufferObject
    edge
    debugGL
    shape2D
    geometry2D
    BSPNode2D
    potentialCollision2D
    gravity2D
    mbState
    mbStateMap
    spring
)
# Xcode and Visual working directories
set_target_properties(mospro PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mospro/")
create_target_launcher(mospro WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/mospro/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
