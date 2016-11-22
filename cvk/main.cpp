#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VKApplication.hpp"
#include "VKDevice.hpp"

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);


    CVK::VKApplication app;
    app.initialize();


    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported" << std::endl;

    std::vector<VkExtensionProperties> instanceExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, instanceExtensions.data());

    for(auto& ext: instanceExtensions)
    {
        std::cout << ext.extensionName << std::endl;
    }    

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}