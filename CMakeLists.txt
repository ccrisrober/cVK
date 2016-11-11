project(vkengine)
cmake_minimum_required(VERSION 3.1)
project(vkengine VERSION 0.1.0 )
set(vkengine_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)

set(COMMON_PROJECT_DOMAIN maldicion069)
set(VKENGINE_DESCRIPTION "vulkan")
set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})
set(VERSION_ABI 0)

include(Common)

# Allow warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

set(VULKAN_LIBRARIES )

common_find_package(glfw)
common_find_package(glm)
common_find_package_post()

set (VKENGINE_DEPENDENT_LIBRARIES glfw glm)

add_subdirectory(src)

include(CPackConfig)
include(DoxygenRule)