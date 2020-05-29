#include "Vulkan/VulkanBuffer.hpp"

uint32_t findMemoryType(Device &device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {

	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(device.physicalDevice, &memoryProperties);

	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
	    if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
	        return i;
	    }
	}

	throw std::runtime_error("GulgEngine can't create find suitable memory type.");
	return 0;
}

Buffer createVulkanBuffer(std::shared_ptr<Device> device, const uint32_t size, const VkBufferUsageFlagBits usage, const VkSharingMode sharing) {

	Buffer newBuffer;

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = sharing;

    checkVulkanError(vkCreateBuffer(device->logicalDevice, &bufferInfo, nullptr, &newBuffer.buffer), "GulgEngine can't create buffer.");

    VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(device->logicalDevice, newBuffer.buffer, &memoryRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;

	try { 

		allocInfo.memoryTypeIndex = findMemoryType(*device,
												   memoryRequirements.memoryTypeBits, 
												   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		checkVulkanError(vkAllocateMemory(device->logicalDevice, &allocInfo, nullptr, &newBuffer.memory), 
						"GulgEngine can't alocate vertex buffer memory.");
	}

	catch(const std::exception &e) { 

		vkDestroyBuffer(device->logicalDevice, newBuffer.buffer, nullptr);
		throw e; 
	}

	vkBindBufferMemory(device->logicalDevice, newBuffer.buffer, newBuffer.memory, 0);

	newBuffer.info.buffer = newBuffer.buffer;
	newBuffer.info.offset = 0;
	newBuffer.info.range = size;

	return newBuffer;
}