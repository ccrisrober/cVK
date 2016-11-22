#ifndef __VK_DEVICE__
#define __VK_DEVICE__

#include <vulkan/vulkan.h>
#include <vector>

namespace CVK
{
	class VKDevice
	{
		struct QueueFamily
		{
			uint32_t graphics;
			uint32_t compute;
		};
	public:
		VKDevice()
		{
        	_device = VK_NULL_HANDLE;
        	_physicalDevice = VK_NULL_HANDLE;
		}
		bool initialize(VKApplication& instance, uint32_t index)
		{
			if (!enumeratePhysicalDevices(instance, index))
			{
				return false;
			}
			if (!queryPhysicalDeviceInfo())
			{
				return false;
			}

			uint32_t queueCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueCount, nullptr);
			if (queueCount < 1)
			{
				// Invalid queue count
				return false;
			}
			_queueFamilyProperties.resize(queueCount);
			vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueCount, _queueFamilyProperties.data());

			QueueFamily qFamily = queryQueueFamily(VK_QUEUE_GRAPHICS_BIT);

			VkResult err = VK_SUCCESS;

			float queueProps[] = { 0.0f };

			VkDeviceQueueCreateInfo queue = {};
			queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue.pNext = nullptr;
			queue.queueFamilyIndex = qFamily.graphics;
			queue.queueCount = 1;
			queue.pQueuePriorities = queueProps;

			std::vector<VkDeviceQueueCreateInfo> queueInfo;
			queueInfo.push_back(queue);

			VkDeviceCreateInfo device = {};
            device.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            device.pNext = nullptr;
            device.queueCreateInfoCount = 1;
            device.pQueueCreateInfos = queueInfo.data();
            device.enabledExtensionCount = 1;
            std::vector<const char *> extensions;
            extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            device.ppEnabledExtensionNames = extensions.data();
            device.pEnabledFeatures = nullptr;
            device.flags = 0;

            err = vkCreateDevice(_physicalDevice, &device, nullptr, &_device);
            if (err != VK_SUCCESS)
            {
               	// Error
                return false;
            }

            return true;
		}
		operator VkDevice()
		{
            return _device;
		}
        operator VkPhysicalDevice()
        {
            return _physicalDevice;
        }
    private:
    	QueueFamily queryQueueFamily(VkQueueFlagBits flags)
    	{
    		QueueFamily f = {};

    		// Find family index for graphics bit
    		if (flags & VK_QUEUE_GRAPHICS_BIT)
    		{
    			for (uint32_t i = 0; i < _queueFamilyProperties.size(); ++i)
    			{
    				if (_queueFamilyProperties[i].queueFlags & flags)
    				{
    					f.graphics = i;
    					break;
    				}
    			}
    		}

    		return f;
    	}
    	bool enumeratePhysicalDevices(VKApplication& instance, uint32_t index)
    	{
    		VkResult err = VK_SUCCESS;

    		uint32_t deviceCount = 0;
    		err = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    		// TODO: Check deviceCount < 1
    		if (err != VK_SUCCESS)
    		{
    			// Error
    			return false;
    		}
    		if (index >= deviceCount)
    		{
    			// Bad index
    			return false;
    		}

    		std::vector<VkPhysicalDevice> devices(deviceCount);
    		err = vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    		if (err != VK_SUCCESS) 
    		{
    			// Error
    			return false;
    		}
    		_physicalDevice = devices[index];

    		return true;
    	}

    	bool queryPhysicalDeviceInfo()
    	{
    		if (_physicalDevice == VK_NULL_HANDLE)
    			return false;

    		vkGetPhysicalDeviceFeatures(_physicalDevice, &_physicalDeviceFeatures);
    		vkGetPhysicalDeviceProperties(_physicalDevice, &_physicalDeviceProperties);
    		vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &_physicalDeviceMemoryProperties);
    	}

        VkDevice                            _device;
        VkPhysicalDevice                    _physicalDevice;
        VkPhysicalDeviceFeatures            _physicalDeviceFeatures;
        VkPhysicalDeviceProperties          _physicalDeviceProperties;
        VkPhysicalDeviceMemoryProperties    _physicalDeviceMemoryProperties;

        std::vector<VkQueueFamilyProperties> _queueFamilyProperties;
	};
}

#endif /* __VK_DEVICE__ */