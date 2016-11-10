set( Name vulkan )
set( NAME VULKAN )
set( namespace vulkan )
set( NAMESPACE VULKAN )
set( INCLUDE_NAME vulkan )

set( VULKAN_SOURCES
  main.cpp
)

set( VULKAN_HEADERS
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set( VULKAN_LINK_LIBRARIES
	${GLFW_LIBRARIES}
)

common_application( vulkan )
