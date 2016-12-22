#include "Includes.hpp"

#include <iostream>

#include "VKApplication.hpp"
#include "VKDevice.hpp"

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);



    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported" << std::endl;

    std::vector<VkExtensionProperties> instanceExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, instanceExtensions.data());

    for(auto& ext: instanceExtensions)
    {
        std::cout << ext.extensionName << std::endl;
    }


    CVK::VKApplication app;
    bool ok = app.initialize(window);

    if (ok)
    {
        CVK::VKDevice dev;
        dev.initialize(app, 0);

        std::cout << "ALL OK" << std::endl;

        /*while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }*/
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}