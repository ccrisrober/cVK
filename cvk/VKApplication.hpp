#ifndef __VK_APPLICATION__
#define __VK_APPLICATION__

#include <vulkan/vulkan.h>
#include <vector>
#include <cstring>

namespace CVK
{
	class VKApplication
	{
	protected:
		VkInstance 					_instance;
		VkApplicationInfo 			_info;
		VkSurfaceKHR 				_window;
		std::vector<std::string> 	_layers;
		std::vector<std::string> 	_extensions;
		std::vector<VkDevice*> 		_devices;
	public:
		VKApplication()
		{
			_instance = VK_NULL_HANDLE;
			_info = {};

			_layers = {
				"VK_LAYER_LUNARG_standart_validation"
			};
		}
		virtual ~VKApplication()
		{

		}
		bool initialize()
		{
			// Check if Vulkan layers are available
			if (!checkInstanceLayers())
			{
				return false;
			}
			// Check if Vulkan required extensions are available
            if (!checkInstanceExtensions())
            {
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

            VkResult err = vkCreateInstance(&ci, nullptr, &_instance);

            if (err != VK_SUCCESS)
            {
            	// Error
            	return false;
            }

            // TODO: DebugCallback

            return true;
		}
		bool isValid()
		{
			return _instance != VK_NULL_HANDLE;
		}
		std::string name() const
		{
			return _info.pApplicationName;
		}
		uint32_t version() const
		{
			return _info.applicationVersion;
		}
		uint32_t enabledLayerCount() const
		{
			return _layers.size();
		}
		operator VkInstance()
		{
			return _instance;
		}
		bool checkInstanceLayers()
		{
			//VkResult err;
			uint32_t instanceLayerSize = 0;
            /*err = */vkEnumerateInstanceLayerProperties(&instanceLayerSize, nullptr);

            std::vector<VkLayerProperties> instanceLayers(instanceLayerSize);
            /*err = */vkEnumerateInstanceLayerProperties(&instanceLayerSize, instanceLayers.data());

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

                if (!found) {
                   	// printf("VKApplication::CheckInstanceLayers() Cannot find Layer: %s\n", layer);
           	     	return false;
                }
        	}

            return true;
		}
		bool checkInstanceExtensions()
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
	};
}

#endif /* __VK_APPLICATION__ */