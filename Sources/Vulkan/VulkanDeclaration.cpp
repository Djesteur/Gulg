#include "Vulkan/VulkanDeclaration.hpp"

std::string getVkResultString(const VkResult result) {

	std::string stringResult;

	switch(result) {

		case VK_SUCCESS:
			stringResult = "VK_SUCCESS | " + std::to_string(0) + "\n";
			stringResult += "Command successfully completed.";
			break;

		case VK_NOT_READY:
			stringResult = "VK_NOT_READY | " + std::to_string(1) + "\n";
			stringResult += "A fence or query has not yet completed.";
			break;

		case VK_TIMEOUT:
			stringResult = "VK_TIMEOUT | " + std::to_string(2) + "\n";
			stringResult += "A wait operation has not completed in the specified time.";
			break;

		case VK_EVENT_SET:
			stringResult = "VK_EVENT_SET | " + std::to_string(3) + "\n";
			stringResult += "An event is signaled.";
			break;

		case VK_EVENT_RESET:
			stringResult = "VK_EVENT_RESET | " + std::to_string(4) + "\n";
			stringResult += "An event is unsignaled.";
			break;

		case VK_INCOMPLETE:
			stringResult = "VK_INCOMPLETE | " + std::to_string(5) + "\n";
			stringResult += " A return array was too small for the result.";
			break;

		case VK_ERROR_OUT_OF_HOST_MEMORY:
			stringResult = "VK_ERROR_OUT_OF_HOST_MEMORY | " + std::to_string(-1) + "\n";
			stringResult += " A host memory allocation has failed.";
			break;

		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			stringResult = "VK_ERROR_OUT_OF_DEVICE_MEMORY | " + std::to_string(-2) + "\n";
			stringResult += "A device memory allocation has failed.";
			break;

		case VK_ERROR_INITIALIZATION_FAILED:
			stringResult = "VK_ERROR_INITIALIZATION_FAILED | " + std::to_string(-3) + "\n";
			stringResult += "Initialization of an object could not be completed for implementation-specific reasons.";
			break;

		case VK_ERROR_DEVICE_LOST:
			stringResult = "VK_ERROR_DEVICE_LOST | " + std::to_string(-4) + "\n";
			stringResult += "The logical or physical device has been lost.";
			break;

		case VK_ERROR_MEMORY_MAP_FAILED:
			stringResult = "VK_ERROR_MEMORY_MAP_FAILED | " + std::to_string(-5) + "\n";
			stringResult += "Mapping of a memory object has failed.";
			break;

		case VK_ERROR_LAYER_NOT_PRESENT:
			stringResult = "VK_ERROR_LAYER_NOT_PRESENT | " + std::to_string(-6) + "\n";
			stringResult += "A requested layer is not present or could not be loaded.";
			break;

		case VK_ERROR_EXTENSION_NOT_PRESENT:
			stringResult = "VK_ERROR_EXTENSION_NOT_PRESENT | " + std::to_string(-7) + "\n";
			stringResult += "A requested extension is not supported.";
			break;

		case VK_ERROR_FEATURE_NOT_PRESENT:
			stringResult = "VK_ERROR_FEATURE_NOT_PRESENT | " + std::to_string(-8) + "\n";
			stringResult += "A requested feature is not supported.";
			break;

		case VK_ERROR_INCOMPATIBLE_DRIVER:
			stringResult = "VK_ERROR_INCOMPATIBLE_DRIVER | " + std::to_string(-9) + "\n";
			stringResult += " The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.";
			break;

		case VK_ERROR_TOO_MANY_OBJECTS:
			stringResult = "VK_ERROR_TOO_MANY_OBJECTS | " + std::to_string(-10) + "\n";
			stringResult += "Too many objects of the type have already been created.";
			break;

		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			stringResult = "VK_ERROR_FORMAT_NOT_SUPPORTED | " + std::to_string(-11) + "\n";
			stringResult += "A requested format is not supported on this device.";
			break;

		case VK_ERROR_FRAGMENTED_POOL:
			stringResult = "VK_ERROR_FRAGMENTED_POOL | " + std::to_string(-12) + "\n";
			stringResult += "A requested pool allocation has failed due to fragmentation of the pool’s memory.";
			break;

		case VK_ERROR_UNKNOWN:
			stringResult = "VK_ERROR_UNKNOWN | " + std::to_string(-13) + "\n";
			stringResult += "Vulkan unknown error";
			break;

		case VK_ERROR_OUT_OF_POOL_MEMORY:
			stringResult = "VK_ERROR_OUT_OF_POOL_MEMORY | " + std::to_string(-1000069000) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_INVALID_EXTERNAL_HANDLE:
			stringResult = "VK_ERROR_INVALID_EXTERNAL_HANDLE | " + std::to_string(-1000072003) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_FRAGMENTATION:
			stringResult = "VK_ERROR_FRAGMENTATION | " + std::to_string(-1000161000) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
			stringResult = "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS | " + std::to_string(-1000257000) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_SURFACE_LOST_KHR:
			stringResult = "VK_ERROR_SURFACE_LOST_KHR | " + std::to_string(-1000000000) + "\n";
			stringResult += "A surface is no longer available.";
			break;

		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			stringResult = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR | " + std::to_string(-1000000001) + "\n";
			stringResult += "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API.";
			break;

		case VK_SUBOPTIMAL_KHR:
			stringResult = "VK_SUBOPTIMAL_KHR | " + std::to_string(1000001003) + "\n";
			stringResult += "A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.";
			break;

		case VK_ERROR_OUT_OF_DATE_KHR:
			stringResult = "VK_ERROR_OUT_OF_DATE_KHR | " + std::to_string(-1000001004) + "\n";
			stringResult += "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface.";
			break;

		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			stringResult = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR | " + std::to_string(-1000003001) + "\n";
			stringResult += "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image.";
			break;

		case VK_ERROR_VALIDATION_FAILED_EXT:
			stringResult = "VK_ERROR_VALIDATION_FAILED_EXT | " + std::to_string(-1000011001) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_INVALID_SHADER_NV:
			stringResult = "VK_ERROR_INVALID_SHADER_NV | " + std::to_string(-1000012000) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
			stringResult = "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT | " + std::to_string(-1000158000) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_NOT_PERMITTED_EXT:
			stringResult = "VK_ERROR_NOT_PERMITTED_EXT | " + std::to_string(-1000174001) + "\n";
			stringResult += "No description.";
			break;

		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
			stringResult = "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT | " + std::to_string(-1000255000) + "\n";
			stringResult += "No description.";
			break;

		case VK_RESULT_MAX_ENUM:
			stringResult = "VK_RESULT_MAX_ENUM | " + std::to_string(0x7FFFFFFF) + "\n";
			stringResult += "No description.";
			break;

		case VK_RESULT_RANGE_SIZE:
			stringResult = "VK_RESULT_RANGE_SIZE | " + std::to_string(VK_RESULT_RANGE_SIZE) + "\n";
			stringResult += "No description.";
			break;

		default:
			stringResult = "This is an bad usage of the getVkResultString function.";
			break;
	}

	return stringResult;
}

void checkVulkanError(const VkResult result, const std::string &errorSentence) {

    if(result != VK_SUCCESS) { throw std::runtime_error("Vulkan error: " + getVkResultString(result) + "\n" + errorSentence); }
}




//If SRGB format is available, pick it. Else, pick the first in list

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {

    for (const VkSurfaceFormatKHR &availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) { 

	for (const VkPresentModeKHR &availablePresentMode: availablePresentModes) {

        if(availablePresentMode == VK_PRESENT_MODE_FIFO_KHR) { return availablePresentMode; }
    }

	return VK_PRESENT_MODE_FIFO_KHR; //The only mode which is always available
}

/*
VK_PRESENT_MODE_IMMEDIATE_KHR: Immediate image draw
VK_PRESENT_MODE_FIFO_KHR: Put in queue, and change with screen refresh (V-sync)
VK_PRESENT_MODE_FIFO_RELAXED_KHR: Same that VK_PRESENT_MODE_FIFO_KHR, but if the queue is empty, draw image in instant
VK_PRESENT_MODE_MAILBOX_KHR: Same that VK_PRESENT_MODE_FIFO_KHR, but if the queue is full, replace image instead of wait
*/

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t windowWidth, uint32_t windowHeight) {

    if (capabilities.currentExtent.width != UINT32_MAX) { return capabilities.currentExtent; } 

    else {

        VkExtent2D actualExtent = {windowWidth, windowHeight};

        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}



SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice &physicalDevice, VkSurfaceKHR &surface) {

    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
    } 

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}