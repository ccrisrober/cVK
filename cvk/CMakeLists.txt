source_group(\\ FILES CMakeLists.txt)

set( CVK_PUBLIC_HEADERS
)

set( CVK_HEADERS )

set( CVK_SOURCES
    main.cpp
)

set( CVK_LINK_LIBRARIES
    ${VULKAN_LIBRARIES}
    glfw
)

common_application( CVK )