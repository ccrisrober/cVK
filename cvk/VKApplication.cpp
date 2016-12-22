#include "VKApplication.hpp"
#include <iostream>

namespace CVK
{
	VKApplication::VKApplication()
	{
		_instance = VK_NULL_HANDLE;
		_info = {};

		_layers = {
			//"VK_LAYER_LUNARG_standart_validation"
		};
	}
	VKApplication::~VKApplication()
	{

	}
	bool VKApplication::initialize(GLFWwindow* window)
	{
		this->_GLwindow = window;
		// Check if Vulkan layers are available
		if (!checkInstanceLayers())
		{
			std::cout << "ERROR INSTANCE LAYERS" << std::endl;
			return false;
		}
		// Check if Vulkan required extensions are available
        if (!checkInstanceExtensions())
        {
			std::cout << "ERROR INSTANCE EXTENSIONS" << std::endl;
            return false;
        }

        _info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        _info.pNext = nullptr;
        _info.pApplicationName = "CVK application";
        _info.applicationVersion = 0;
        _info.pEngineName = "CVK";
        _info.engineVersion = 0;
        _info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo ci;
        ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        ci.pNext = nullptr;
        ci.flags = 0;
        ci.pApplicationInfo = &_info;
        ci.enabledLayerCount = _layers.size();
        std::vector<const char*> layers(ci.enabledLayerCount);
        for(const auto& str: _layers)
        {
        	layers.push_back(str.c_str());
        }
        ci.ppEnabledLayerNames = layers.data();
        ci.enabledExtensionCount = _extensions.size();
        std::vector<const char*> extensions(ci.enabledExtensionCount);
        for(const auto& str: _extensions)
        {
        	extensions.push_back(str.c_str());
        }
        ci.ppEnabledExtensionNames = extensions.data();

        std::cout << "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO OK" << std::endl;

        VkResult err = vkCreateInstance(&ci, nullptr, &_instance);
    	std::cout << "CREATING INSTANCE" << std::endl;

        if (err != VK_SUCCESS)
        {
        	std::cout << "ERROR CREATING INSTANCE" << std::endl;
        	// Error
        	return false;
        }

        if(!setupDebugCb())
        {
        	std::cout << "ERROR SETUP DEBUGCB" << std::endl;
            return false;
        }

        std::cout << "PPLICATION OK" << std::endl;

        return true;
	}
	bool VKApplication::isValid()
	{
		return _instance != VK_NULL_HANDLE;
	}
	std::string VKApplication::name() const
	{
		return _info.pApplicationName;
	}
	uint32_t VKApplication::version() const
	{
		return _info.applicationVersion;
	}
	uint32_t VKApplication::enabledLayerCount() const
	{
		return _layers.size();
	}
	VKApplication::operator VkInstance()
	{
		return _instance;
	}
	bool VKApplication::checkInstanceLayers()
	{
		VkResult err;
		uint32_t instanceLayerSize = 0;
        err = vkEnumerateInstanceLayerProperties(&instanceLayerSize, nullptr);

        if (err != VK_SUCCESS)
        {
        	std::cout << "ERROR BUSCANDO NÚMERO LAYERS" << std::endl;
        }

        std::vector<VkLayerProperties> instanceLayers(instanceLayerSize);
        err = vkEnumerateInstanceLayerProperties(&instanceLayerSize, instanceLayers.data());

        if (err != VK_SUCCESS)
        {
        	std::cout << "ERROR LLENANDO ARRAY DE NÚMERO LAYERS" << std::endl;
        }

        for (auto layer : _layers)
        {
            bool found = false;

            for (auto &layerProp : instanceLayers)
            {
                if (layer == layerProp.layerName)
                {
                    found = true;
                }
            }

            if (!found)
            {
            	std::cout << "Cannot find layer " << layer << std::endl;
       	     	return false;
            }
    	}

        return true;
	}
	bool VKApplication::checkInstanceExtensions()
	{
		uint32_t instanceSize = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &instanceSize, nullptr);

		std::vector<VkExtensionProperties> instanceExtensions(instanceSize);
		vkEnumerateInstanceExtensionProperties(nullptr, &instanceSize, instanceExtensions.data());

		for (auto& ext: instanceExtensions)
		{
			// Enable validation extension layer
			if (!strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, ext.extensionName))
			{
                _extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			}
			if(!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, ext.extensionName))
			{
				_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
			}

			/*#if WIN32
			if (!strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, ext.extensionName))
			{
                _extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
			}
			#else
			if (!strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, ext.extensionName))
			{
                _extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
			}
			#endif*/
		}
		return true;
	}
    VKAPI_ATTR VkBool32 VKAPI_CALL VKApplication::DebugCallback(VkFlags msgFlags,
        VkDebugReportObjectTypeEXT /*objType*/,
        uint64_t /*srcObject*/, size_t /*location*/,
        int32_t /*msgCode*/, const char* /*pLayerPrefix*/,
        const char* /*pMsg*/, void* /*pUserData*/)
    {
        if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
        {
            // Error
        }
        else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
        {
            // Error
        }
        else {
            return false;
        }

        /*
        * false indicates that layer should not bail-out of an
        * API call that had validation failures. This may mean that the
        * app dies inside the driver due to invalid parameter(s).
        * That's what would happen without validation layers, so we'll
        * keep that behavior here.
        */
        return false;

    }

	bool VKApplication::setupDebugCb()
	{
		VkResult err;

		//Get debug callback function pointers
        fpCreateDebugReportCallback =
            (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
            	_instance, "vkCreateDebugReportCallbackEXT");
        fpDestroyDebugReportCallback =
            (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
            	_instance, "vkDestroyDebugReportCallbackEXT");
		
        if (!fpCreateDebugReportCallback)
        {
        	return false;
        }
        if (!fpDestroyDebugReportCallback)
        {
        	return false;
        }

        fpDebugReportMessage =
            (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(
            	_instance, "vkDebugReportMessageEXT");
        if (!fpDebugReportMessage)
       	{
            return false;
        }

        PFN_vkDebugReportCallbackEXT cb;
        cb = VKApplication::DebugCallback;

        VkDebugReportCallbackCreateInfoEXT dbgci;
        dbgci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        dbgci.pNext = nullptr;
        dbgci.pfnCallback = cb;
        dbgci.pUserData = nullptr;
        dbgci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        err = fpCreateDebugReportCallback(_instance, &dbgci, nullptr, &_debugReportCallback);

        if (err == VK_ERROR_OUT_OF_HOST_MEMORY)
        {
        	// Out of host memory
        	return false;
        } else if (err != VK_SUCCESS)
        {
        	// Error
        	return false;
        }
        return true;
	}
}