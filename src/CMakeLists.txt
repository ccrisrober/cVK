set( Name vkengine )
set( NAME VKENGINE )
set( namespace vkengine )
set( NAMESPACE VKENGINE )
set( INCLUDE_NAME vkengine )

set( VKENGINE_SOURCES
  main.cpp
)

set( VKENGINE_HEADERS
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set( VKENGINE_LINK_LIBRARIES
	glfw
)

common_application( vkengine )
