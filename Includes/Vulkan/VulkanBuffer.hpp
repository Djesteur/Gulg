#ifndef VULKAN_BUFFER_HPP
#define VULKAN_BUFFER_HPP

#define GLFW_INCLUDE_VULKAN
#include <Libraries/GLFW/glfw3.h>

#include "Vulkan/VulkanDeclaration.hpp"
#include "Vulkan/VulkanDevice.hpp"

struct Buffer {

	Buffer() {}

	void write(std::shared_ptr<Device> device, const void *source, const size_t size) {

		void* data;
		vkMapMemory(device->logicalDevice, memory, 0, size, 0, &data);
		memcpy(data, source, size);
		vkUnmapMemory(device->logicalDevice, memory);
	}

	void clean(std::shared_ptr<Device> device) {

		vkFreeMemory(device->logicalDevice, memory, nullptr);
		vkDestroyBuffer(device->logicalDevice, buffer, nullptr);
	}

	VkBuffer buffer;
	VkDeviceMemory memory;
	VkDescriptorBufferInfo info;

	uint32_t size;
};


Buffer createVulkanBuffer(std::shared_ptr<Device> device, const uint32_t size, const VkBufferUsageFlagBits usage, const VkSharingMode sharing);

#endif