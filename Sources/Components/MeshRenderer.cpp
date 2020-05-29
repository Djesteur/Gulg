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

	m_vertexBuffer = createVulkanBuffer(m_device, sizeof(glm::vec3) * mesh.m_finalArray.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);

	try {

		m_indexBuffer = createVulkanBuffer(m_device, sizeof(uint32_t) * mesh.m_indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
	}

	catch(const std::exception &e) { 

		m_vertexBuffer.clean(m_device);
		throw e; 
	}

	try {

		m_uniformBuffer = createVulkanBuffer(m_device, sizeof(glm::mat4) *3, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
	}

	catch(const std::exception &e) { 

		m_indexBuffer.clean(m_device);
		m_vertexBuffer.clean(m_device);
		throw e; 
	}
	

	m_vertexBuffer.write(m_device, mesh.m_finalArray.data(), sizeof(glm::vec3) * mesh.m_finalArray.size());
	m_indexBuffer.write(m_device, mesh.m_indices.data(), sizeof(uint32_t) * mesh.m_indices.size());

	m_nbIndices = mesh.m_indices.size();

	try {

		m_pipeline = createVulkanPipeline(m_device, "Datas/Shaders/vert.spv", "Datas/Shaders/frag.spv");
		fillSubmitInfos(m_device, m_pipeline);
	}

	catch(const std::exception &e) { 

		m_uniformBuffer.clean(m_device);
		m_indexBuffer.clean(m_device);
		m_vertexBuffer.clean(m_device);

		throw e; 
	}

	try { createDescriptorSets(); }

	catch(const std::exception &e) { 

		m_pipeline.clean(m_device);

		m_uniformBuffer.clean(m_device);
		m_indexBuffer.clean(m_device);
		m_vertexBuffer.clean(m_device);

		throw e; 
	}


	try { createCommandBuffers(); }

	catch(const std::exception &e) { 

		m_pipeline.clean(m_device);

		m_uniformBuffer.clean(m_device);
		m_indexBuffer.clean(m_device);
		m_vertexBuffer.clean(m_device);

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
        vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 1, &m_vertexBuffer.buffer, &offsets);
        vkCmdBindIndexBuffer(m_commandBuffers[i], m_indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline.pipelineLayout, 0, 1,
                            &m_descriptorSets[0], 0, nullptr);

        vkCmdDrawIndexed(m_commandBuffers[i], static_cast<uint32_t>(m_nbIndices), 1, 0, 0, 0);

		vkCmdEndRenderPass(m_commandBuffers[i]);

		checkVulkanError(vkEndCommandBuffer(m_commandBuffers[i]), "GulgEngine can't end recording command buffer.");
	}
}

void MeshRenderer::createDescriptorSets() {

	VkDescriptorSetAllocateInfo alloc_info[1];
    alloc_info[0].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc_info[0].descriptorPool = m_pipeline.descriptorPool;
    alloc_info[0].descriptorSetCount = 1;
    alloc_info[0].pSetLayouts = m_pipeline.descriptorSetLayout.data();

    
    m_descriptorSets.resize(1);

    checkVulkanError(vkAllocateDescriptorSets(m_device->logicalDevice, alloc_info, m_descriptorSets.data()), 
    				 "GulgEngine can't end recording command buffer.");

    VkWriteDescriptorSet writes[1];

    writes[0] = {};
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = m_descriptorSets[0];
    writes[0].descriptorCount = 1;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writes[0].pBufferInfo = &m_uniformBuffer.info;
    writes[0].dstArrayElement = 0;
    writes[0].dstBinding = 0;

    vkUpdateDescriptorSets(m_device->logicalDevice, 1, writes, 0, nullptr);
}


void MeshRenderer::clean() {

	if(m_wellInitialized) {

		m_uniformBuffer.clean(m_device);
		m_indexBuffer.clean(m_device);
		m_vertexBuffer.clean(m_device);

		m_pipeline.clean(m_device);
		m_wellInitialized = false;
	}
}

}}