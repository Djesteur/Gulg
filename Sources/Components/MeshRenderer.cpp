#include "Components/MeshRenderer.hpp"

namespace Gg {

namespace Component {

MeshRenderer::MeshRenderer(std::shared_ptr<Device> device): 
	m_device{device},
	m_wellInitialized{false} {}

MeshRenderer::MeshRenderer(std::shared_ptr<Device> device, const Mesh &mesh): 
	m_device{device},
	m_wellInitialized{false} {

	loadFromMesh(mesh);
}

MeshRenderer::MeshRenderer(const MeshRenderer &renderer): 
	m_device{renderer.m_device},
	m_wellInitialized{renderer.m_wellInitialized} {}

void MeshRenderer::operator=(const MeshRenderer &renderer) {

	m_device = renderer.m_device;
	m_wellInitialized = false;
}

std::shared_ptr<AbstractComponent> MeshRenderer::clone() const {

	return nullptr;
}

MeshRenderer::~MeshRenderer() { clean(); }

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


void MeshRenderer::loadFromMesh(const Mesh &mesh) {

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(glm::vec3) * mesh.m_finalArray.size();
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    checkVulkanError(vkCreateBuffer(m_device->logicalDevice, &bufferInfo, nullptr, &m_verticesBuffer), "GulgEngine can't create vertex buffer.");

    VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(m_device->logicalDevice, m_verticesBuffer, &memoryRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;

	try { 

		allocInfo.memoryTypeIndex = findMemoryType(*m_device,
												   memoryRequirements.memoryTypeBits, 
												   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		checkVulkanError(vkAllocateMemory(m_device->logicalDevice, &allocInfo, nullptr, &m_verticesBufferMemory), 
						"GulgEngine can't alocate vertex buffer memory.");
	}

	catch(const std::exception &e) { 

		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);
		throw e; 
	}

	vkBindBufferMemory(m_device->logicalDevice, m_verticesBuffer, m_verticesBufferMemory, 0);

	void* data;
	vkMapMemory(m_device->logicalDevice, m_verticesBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, mesh.m_finalArray.data(), static_cast<size_t> (bufferInfo.size));
	vkUnmapMemory(m_device->logicalDevice, m_verticesBufferMemory);


	VkBufferCreateInfo bufferInfoIndices = {};
	bufferInfoIndices.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfoIndices.size = sizeof(uint32_t) * mesh.m_indices.size();
	bufferInfoIndices.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	bufferInfoIndices.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	try { 

		checkVulkanError(vkCreateBuffer(m_device->logicalDevice, &bufferInfoIndices, nullptr, &m_indexBuffer), "GulgEngine can't create indice buffer.");
	}

	catch(const std::exception &e) { 

		vkFreeMemory(m_device->logicalDevice, m_verticesBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);
		throw e; 
	}

 
	try { 

		checkVulkanError(vkAllocateMemory(m_device->logicalDevice, &allocInfo, nullptr, &m_indexBufferMemory), 
						"GulgEngine can't alocate vertex buffer memory.");
	}

	catch(const std::exception &e) { 

		vkDestroyBuffer(m_device->logicalDevice, m_indexBuffer, nullptr);
		vkFreeMemory(m_device->logicalDevice, m_verticesBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);
		throw e; 
	}

	vkBindBufferMemory(m_device->logicalDevice, m_indexBuffer, m_indexBufferMemory, 0);

	vkMapMemory(m_device->logicalDevice, m_indexBufferMemory, 0, bufferInfoIndices.size, 0, &data);
	memcpy(data, mesh.m_indices.data(), static_cast<size_t> (bufferInfoIndices.size));
	vkUnmapMemory(m_device->logicalDevice, m_indexBufferMemory);

	m_nbIndices = mesh.m_indices.size();

	try {

		m_pipeline = createVulkanPipeline(m_device, "Datas/Shaders/vert.spv", "Datas/Shaders/frag.spv");
		fillSubmitInfos(m_device, m_pipeline);
	}

	catch(const std::exception &e) { 

		vkFreeMemory(m_device->logicalDevice, m_indexBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_indexBuffer, nullptr);

		vkFreeMemory(m_device->logicalDevice, m_verticesBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);
		throw e; 
	}

	try { createCommandBuffers(); }

	catch(const std::exception &e) { 

		m_pipeline.clean(m_device);

		vkFreeMemory(m_device->logicalDevice, m_indexBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_indexBuffer, nullptr);

		vkFreeMemory(m_device->logicalDevice, m_verticesBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);

		throw e; 
	}

	m_wellInitialized = true;
}

void MeshRenderer::draw() {

	m_pipeline.submitInfo.pCommandBuffers = &m_commandBuffers[m_device->currentImageIndex];

	checkVulkanError(vkQueueSubmit(m_device->graphicsQueue, 1, &m_pipeline.submitInfo, VK_NULL_HANDLE), "GulgEngine can't submit draw command buffer.");
}

void MeshRenderer::createCommandBuffers() {

	m_commandBuffers.resize(m_pipeline.framebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_device->commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

	checkVulkanError(vkAllocateCommandBuffers(m_device->logicalDevice, &allocInfo, m_commandBuffers.data()), 
					 "GulgEngine can't create VkCommandBuffer.");

	for (size_t i{0}; i < m_commandBuffers.size(); i++) {

	    VkCommandBufferBeginInfo beginInfo = {};
	    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	    checkVulkanError(vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo), "GulgEngine can't begin recording command buffer.");

	    VkExtent2D extent{m_device->width, m_device->height};

	    VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_pipeline.renderPass;
		renderPassInfo.framebuffer = m_pipeline.framebuffers[i];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = extent;


		VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline.pipeline);

        VkDeviceSize offsets = 0;
        vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 1, &m_verticesBuffer, &offsets);
        vkCmdBindIndexBuffer(m_commandBuffers[i], m_indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        vkCmdDrawIndexed(m_commandBuffers[i], static_cast<uint32_t>(m_nbIndices), 1, 0, 0, 0);

		vkCmdEndRenderPass(m_commandBuffers[i]);

		checkVulkanError(vkEndCommandBuffer(m_commandBuffers[i]), "GulgEngine can't end recording command buffer.");
	}
}


void MeshRenderer::clean() {

	if(m_wellInitialized) {

		vkFreeMemory(m_device->logicalDevice, m_indexBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_indexBuffer, nullptr);

		vkFreeMemory(m_device->logicalDevice, m_verticesBufferMemory, nullptr);
		vkDestroyBuffer(m_device->logicalDevice, m_verticesBuffer, nullptr);

		m_pipeline.clean(m_device);
		m_wellInitialized = false;
	}
}

}}