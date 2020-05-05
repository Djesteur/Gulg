#ifndef VULKAN_DEVICE_HPP
#define VULKAN_DEVICE_HPP

#include <set>
#include <memory>

#define GLFW_INCLUDE_VULKAN
#include <Libraries/GLFW/glfw3.h>

#include "Vulkan/VulkanDeclaration.hpp"

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {

    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;

    bool isComplete() { return graphics.has_value() && present.has_value(); }
};

struct Device {

	Device() {}

	void clean() {

		vkDestroySemaphore(logicalDevice, readyForPresent, nullptr);
		vkDestroySemaphore(logicalDevice, readyForGraphics, nullptr);
		vkDestroyCommandPool(logicalDevice, commandPool, nullptr);

		for(VkImageView current_view: imageViews) { vkDestroyImageView(logicalDevice, current_view, nullptr); }

		vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);
		vkDestroyDevice(logicalDevice, nullptr);
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);
	}

	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;

	std::vector<VkImage> images;
	std::vector<VkImageView> imageViews;

	VkCommandPool commandPool;
	VkSemaphore readyForGraphics, readyForPresent;

	uint32_t currentImageIndex;

	VkPresentInfoKHR presentInfo;

	uint32_t width, height;
};


std::shared_ptr<Device> createVulkanDevice(GLFWwindow *window, const uint32_t width, const uint32_t height);

#endif