#ifndef ROASTENGINE_VKRENDERER_H
#define ROASTENGINE_VKRENDERER_H
#define GLFW_INCLUDE_VULKAN
#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include "../utils.h"

class vkRenderer {

public:
    vkRenderer();
    int     init(GLFWwindow *newWindow);
    void    cleanup();
    ~vkRenderer();

private:
    GLFWwindow              *w{};

    // Vulkan Instance
    VkInstance              instance{};

    struct {
        VkPhysicalDevice    physicalDevice;
        VkDevice            logicalDevice;
    } mainDevice{};

    VkQueue         graphicsQueue{};
    VkQueue         presentationQueue{};
    VkSurfaceKHR    surface{};
    VkSwapchainKHR  swapChain{};

    VkFormat        swapChainImageFormat{};
    VkExtent2D      swapChainExtent{};

    // Instance Support
    void createInstance();

    // Devices Support
    void createPhysicalDevices();
    void createLogicalDevice();
    void createSurface();

    // Swapchain
    void                createSwapChain();
    VkSurfaceFormatKHR  chooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats);
    VkPresentModeKHR    chooseBestPresentationMode(const std::vector<VkPresentModeKHR> presentationModes);
    VkExtent2D          chooseSwapExtent(const VkSurfaceCapabilitiesKHR &surfaceCapabilities);

    // Extension Support
    bool checkInstanceExtensionSupport  (std::vector<const char*> *checkExtensions);
    bool extensionInList                (std::vector<VkExtensionProperties> &extensions, const char *const &checkExtension) const;

    // Device Support
    bool                deviceIsSuitable(VkPhysicalDevice device);
    bool                checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndexes  getQueueFamilies(VkPhysicalDevice device);
    SwapChainDetails    getSwapChainDetails(VkPhysicalDevice device);


    // Validation layers
    // TODO: creation and clean handling

    // Debug Implementation (Validation Layers)
    VkDebugUtilsMessengerEXT debugMessenger{};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };


    bool checkValidationLayerSupport();

    std::vector<const char *> getRequiredExtensions();

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                       VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    void setupDebugMessenger();
};

#endif //ROASTENGINE_VKRENDERER_H
