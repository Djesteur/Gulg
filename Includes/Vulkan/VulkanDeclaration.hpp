#ifndef VULKAN_DECLARATION_HPP
#define VULKAN_DECLARATION_HPP

#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <Libraries/glm/glm.hpp>

#define GLFW_INCLUDE_VULKAN
#include <Libraries/GLFW/glfw3.h>

#include "Logger.hpp"



struct SwapChainSupportDetails {

    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t windowWidth, uint32_t windowHeight);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice &physicalDevice, VkSurfaceKHR &surface);


std::string getVkResultString(const VkResult result);

void checkVulkanError(const VkResult result, const std::string &errorSentence);

#endif