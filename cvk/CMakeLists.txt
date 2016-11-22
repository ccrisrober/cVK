source_group(\\ FILES CMakeLists.txt)

set( CVK_PUBLIC_HEADERS
	VkApplication.hpp
	VKDevice.hpp
)

set( CVK_HEADERS )

set( CVK_SOURCES
    main.cpp
)

set( CVK_LINK_LIBRARIES
    ${VULKAN_LIBRARY}
    glfw
)

common_application( CVK )