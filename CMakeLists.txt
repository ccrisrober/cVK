cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(CVK VERSION 0.1.0 )
set(CVK_VERSION_ABI 1)

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
	message( FATAL "no in source building allowed." )
endif()

list(APPEND CMAKE_MODULE_PATH 
	${PROJECT_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/common)

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
	add_definitions( -DDEBUG )
endif( )

include(GitExternal)

set(CVK_DESCRIPTION "CVK")
set(COMMON_PROJECT_DOMAIN maldicion069)

include(Common)

common_find_package( GLM REQUIRED )
common_find_package( Boost COMPONENTS unit_test_framework )
common_find_package( Vulkan REQUIRED )
common_find_package( GLFW )

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

list (APPEND CVK_LIBRARIES GLM GLFW Vulkan)

common_find_package_post()

add_subdirectory(cvk)
