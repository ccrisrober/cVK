#ifndef __VK_APPLICATION__
#define __VK_APPLICATION__

#include "Includes.hpp"
#include <vector>
#include <string>
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

		GLFWwindow* _GLwindow;
	public:
		VKApplication();
		virtual ~VKApplication();
		bool initialize(GLFWwindow* window);
		bool isValid();
		std::string name() const;
		uint32_t version() const;
		uint32_t enabledLayerCount() const;
		operator VkInstance();
		bool checkInstanceLayers();
		bool checkInstanceExtensions();
        VkDebugReportCallbackEXT _debugReportCallback;
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType,
			uint64_t srcObject, size_t location, int32_t msgCode,
			const char *pLayerPrefix, const char *pMsg, void *pUserData);

		PFN_vkCreateDebugReportCallbackEXT fpCreateDebugReportCallback;
        PFN_vkDestroyDebugReportCallbackEXT fpDestroyDebugReportCallback;
        PFN_vkDebugReportMessageEXT fpDebugReportMessage;

		bool setupDebugCb();
	};
}

#endif /* __VK_APPLICATION__ */