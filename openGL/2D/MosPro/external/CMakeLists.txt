if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###


set(GLFW_SOURCE	
	glfw-2.7.9/lib/enable.c 
	glfw-2.7.9/lib/fullscreen.c 
	glfw-2.7.9/lib/glext.c 
	glfw-2.7.9/lib/image.c 
	glfw-2.7.9/lib/init.c 
	glfw-2.7.9/lib/input.c 
	glfw-2.7.9/lib/joystick.c 
	glfw-2.7.9/lib/stream.c 
	glfw-2.7.9/lib/tga.c 
	glfw-2.7.9/lib/thread.c 
	glfw-2.7.9/lib/time.c 
	glfw-2.7.9/lib/window.c
)


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7.9/lib/win32/win32_enable.c 
	glfw-2.7.9/lib/win32/win32_fullscreen.c 
	glfw-2.7.9/lib/win32/win32_glext.c 
	glfw-2.7.9/lib/win32/win32_init.c 
	glfw-2.7.9/lib/win32/win32_joystick.c 
	glfw-2.7.9/lib/win32/win32_thread.c 
	glfw-2.7.9/lib/win32/win32_time.c 
	glfw-2.7.9/lib/win32/win32_window.c 
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7.9/lib/x11/x11_enable.c 
	glfw-2.7.9/lib/x11/x11_fullscreen.c 
	glfw-2.7.9/lib/x11/x11_glext.c 
	glfw-2.7.9/lib/x11/x11_init.c 
	glfw-2.7.9/lib/x11/x11_joystick.c 
	glfw-2.7.9/lib/x11/x11_keysym2unicode.c 
	glfw-2.7.9/lib/x11/x11_thread.c 
	glfw-2.7.9/lib/x11/x11_time.c 
	glfw-2.7.9/lib/x11/x11_window.c
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(GLFW_OBJC_SOURCE
	glfw-2.7.9/lib/cocoa/cocoa_enable.m 
	glfw-2.7.9/lib/cocoa/cocoa_fullscreen.m 
	glfw-2.7.9/lib/cocoa/cocoa_glext.m 
	glfw-2.7.9/lib/cocoa/cocoa_init.m 
	glfw-2.7.9/lib/cocoa/cocoa_joystick.m 
	glfw-2.7.9/lib/cocoa/cocoa_thread.c 
	glfw-2.7.9/lib/cocoa/cocoa_time.m 
	glfw-2.7.9/lib/cocoa/cocoa_window.m 
)
set(GLFW_SOURCE	${GLFW_SOURCE} ${GLFW_OBJC_SOURCE})

set_source_files_properties(${GLFW_SOURCE} 
	PROPERTIES COMPILE_FLAGS "-x objective-c") #-fobjc-exceptions


#add_definitions(-D_MACOSX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(GLFW_HEADERS
	glfw-2.7.9/lib/win32/platform.h
	glfw-2.7.9/lib/internal.h
)
include_directories(
	glfw-2.7.9/lib/win32/
	glfw-2.7.9/lib/
	glfw-2.7.9/include/
	glew-1.9.0/include/
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLFW_HEADERS
	glfw-2.7.9/lib/x11/platform.h
	glfw-2.7.9/lib/internal.h
)
include_directories(
	glfw-2.7.9/lib/x11/
	glfw-2.7.9/lib/
	glfw-2.7.9/include/
	glew-1.9.0/include/
)
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
)
#Since there is no easy way to choose between _GLFW_HAS_GLXGETPROCADDRESS, _GLFW_HAS_GLXGETPROCADDRESSARB, _GLFW_HAS_GLXGETPROCADDRESSEXT and _GLFW_HAS_DLOPEN,
#I force the latter, which as least should exist (and work?) everywhere.
add_definitions(
	-D_GLFW_HAS_DLOPEN
	-D_GLFW_HAS_XRANDR
)
add_definitions(-D_UNIX)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(GLFW_HEADERS
	glfw-2.7.9/lib/cocoa/platform.h
	glfw-2.7.9/lib/internal.h
)
include_directories(
	glfw-2.7.9/lib/cocoa/
	glfw-2.7.9/lib/
	glfw-2.7.9/include/
	glew-1.9.0/include/
)
SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL -framework IOKit -framework Foundation -framework AppKit")
add_definitions(-D_MACOSX -ObjC++)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


add_library( GLFW_279 STATIC
	${GLFW_SOURCE}
	${GLFW_HEADERS}
)

target_link_libraries(GLFW_279
	${OPENGL_LIBRARY}
)

### GLEW ###

set(GLEW_SOURCE
	glew-1.9.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_190 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_190
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

### ASSIMP ###
# AssImp already has a CMakeLists.txt so let's use these

# Compile built-in, modified version of Zlib
include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckFunctionExists)
#add_subdirectory( assimp-3.0.1270/contrib/zlib )

# Compile without Boost
include_directories( assimp-3.0.1270/code/BoostWorkaround )
add_definitions( -DASSIMP_BUILD_BOOST_WORKAROUND )

# Compile AssImp
set( LIB_INSTALL_DIR "lib")
set(LIBASSIMP_COMPONENT libassimp3.0-r1270-OGLtuts)
set(ZLIB_LIBRARIES zlib)
set(BUILD_STATIC_LIB ON)
#set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib)
#add_subdirectory( assimp-3.0.1270/code )
