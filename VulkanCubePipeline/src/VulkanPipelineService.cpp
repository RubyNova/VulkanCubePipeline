#include "../include/VulkanPipelineService.h"

void VulkanPipelineService::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(glfwCreateWindow(_width, _height, "Vulkan window", nullptr, nullptr), glfwDestroyWindow);
}

bool VulkanPipelineService::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : _validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (std::strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

void VulkanPipelineService::createInstance() {
    if (_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

    if (_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
        createInfo.ppEnabledLayerNames = _validationLayers.data();

        debugCreateInfo = getDebugMessengerCreateInfo();
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    uint32_t vkExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);

    std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());

    std::cout << "Available VK Extensions:" << std::endl;
    for (const auto& extension : vkExtensions) {
        std::cout << '\t' << extension.extensionName << std::endl;
    }

    std::cout << std::endl;

    bool glfwExtensionsFound = true;
    bool extensionFound = false;

    for (size_t i = 0; i < glfwExtensionCount; i++) {
        extensionFound = false;

        for (const auto& extension : vkExtensions) {
            if (std::string(extension.extensionName) != std::string(glfwExtensions[i])) {
                continue;
            }
            extensionFound = true;
        }

        if (!extensionFound) {
            glfwExtensionsFound = false;
            break;
        }
    }

    if (glfwExtensionsFound) {
        std::cout << "Required extensions for GLFW found!" << std::endl;
    }
    else {
        throw std::runtime_error("Unable to find extensions required by GLFW! Aborting.");
    }

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (_enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &_instance);

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanPipelineService::setupDebugMessenger() {
    if (!_enableValidationLayers) {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo = getDebugMessengerCreateInfo();

    if (createDebugUtilsMessengerEXTViaProcAddress(_instance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanPipelineService::initVulkan() {
    createInstance();
    setupDebugMessenger();
}

void VulkanPipelineService::mainLoop() {
    while (!glfwWindowShouldClose(_window.get())) {
        glfwPollEvents();
    }
}

void VulkanPipelineService::cleanup() {
    if (_enableValidationLayers) {
        //destroyDebugUtilsMessengerEXTViaProcAddress(_instance, _debugMessenger, nullptr);
    }

    vkDestroyInstance(_instance, nullptr);

    glfwDestroyWindow(_window.get());

    glfwTerminate();
}

VulkanPipelineService::VulkanPipelineService() noexcept : _window(nullptr, nullptr), _debugMessenger(), _instance() {
}

void VulkanPipelineService::launch() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}
