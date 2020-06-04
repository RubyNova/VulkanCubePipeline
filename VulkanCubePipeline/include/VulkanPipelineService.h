#ifndef VULKANPIPELINESERVICE_H
#define VULKANPIPELINESERVICE_H

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <cstdint>
#include <vector>

inline VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

class VulkanPipelineService {
private:
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
	const uint32_t _width = 800;
	const uint32_t _height = 600;
	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debugMessenger;

	const std::vector<const char*> _validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool _enableValidationLayers = false;
#else
	const bool _enableValidationLayers = true;
#endif

	static VkResult createDebugUtilsMessengerEXTViaProcAddress(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	static void destroyDebugUtilsMessengerEXTViaProcAddress(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	static VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo() {
		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
		return createInfo;
	}

	void initWindow();
	bool checkValidationLayerSupport();
	void createInstance();
	void setupDebugMessenger();
	void initVulkan();
	void mainLoop();
	void cleanup();
public:
	VulkanPipelineService() noexcept;
	void launch();
};

#endif // !VULKANPIPELINESERVICE_H
