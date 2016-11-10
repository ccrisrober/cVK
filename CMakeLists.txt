# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   TEVimos
#   2016 (c) Universidad Rey Juan Carlos
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

project(vulkan)
cmake_minimum_required(VERSION 3.1)
project( vulkan VERSION 0.1.0 )
set( tevimos_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

include(GitExternal)

set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})
set(VERSION_ABI 0)

include(Common)

set(COMMON_PROJECT_DOMAIN gmrv.es)
set(VULKAN_DESCRIPTION "vulkan")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
option( VULKAN_OPTIONALS_AS_REQUIRED
  "Force optional dependencies as required" ON )
if ( VULKAN_OPTIONALS_AS_REQUIRED )
  set( VULKAN_OPTS_FIND_ARGS "REQUIRED" )
else()
  set( VULKAN_OPTS_FIND_ARGS "" )
endif()

common_find_package(GLFW REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

list(APPEND VULKAN_DEPENDENT_LIBRARIES GLFW)

common_find_package_post( )

set( PROJECT_INCLUDE_NAME vulkan )

add_subdirectory( vulkan )

install( FILES ${PROJECT_BINARY_DIR}/include/vulkan/defines.h
  DESTINATION include/vulkan )
install( FILES ${PROJECT_BINARY_DIR}/include/vulkan/defines${SYSTEM}.h
  DESTINATION include/vulkan )

#include( CPackConfig )
