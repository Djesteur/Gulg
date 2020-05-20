#include "Vulkan/VulkanPipeline.hpp"

// ----- Accessible only inside the file ----- //



//Pipeline creation

void loadShadersFromFiles(std::shared_ptr<Device> device, VkShaderModule &shaderModule, const std::string &path);
void createDescriptorSetLayout(std::shared_ptr<Device> device, Pipeline &pipeline);
void createPipelineLayout(std::shared_ptr<Device> device, Pipeline &pipeline);
void createRenderPass(std::shared_ptr<Device> device, Pipeline &pipeline);
void createPipeline(std::shared_ptr<Device> device, Pipeline &pipeline);
void createFramebuffers(std::shared_ptr<Device> device, Pipeline &pipeline);

std::vector<char> readFile(const std::string &path);
VkShaderModule createShaderModule(std::shared_ptr<Device> device, const std::vector<char> &code);

VkVertexInputBindingDescription getBindingDescription();
std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();







void loadShaderFromFile(std::shared_ptr<Device> device, VkShaderModule &shaderModule, const std::string &path) {

	std::vector<char> code{readFile(path)};
	shaderModule = createShaderModule(device, code);
}

void createDescriptorSetLayout(std::shared_ptr<Device> device, Pipeline &pipeline) {

	VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	checkVulkanError(vkCreateDescriptorSetLayout(device->logicalDevice, &layoutInfo, nullptr, &pipeline.descriptorSetLayout),
					 "GulgEngine can't create VkDescriptorSetLayout.");
	
}

void createPipelineLayout(std::shared_ptr<Device> device, Pipeline &pipeline) {

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &pipeline.descriptorSetLayout;

	checkVulkanError(vkCreatePipelineLayout(device->logicalDevice, &pipelineLayoutInfo, nullptr, &pipeline.pipelineLayout), 
					 "GulgEngine can't create VkPipelineLayout.");
}

void createRenderPass(std::shared_ptr<Device> device, Pipeline &pipeline) {

	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device->physicalDevice, device->surface);

	VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = chooseSwapSurfaceFormat(swapChainSupport.formats).format;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	checkVulkanError(vkCreateRenderPass(device->logicalDevice, &renderPassInfo, nullptr, &pipeline.renderPass), "GulgEngine can't create VkRenderPass.");
}

void createPipeline(std::shared_ptr<Device> device, Pipeline &pipeline) {

	VkPipelineShaderStageCreateInfo vertexStageInfo = {};
	vertexStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexStageInfo.module = pipeline.vertexModule;
	vertexStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragmentStageInfo = {};
	fragmentStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragmentStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragmentStageInfo.module = pipeline.fragmentModule;
	fragmentStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertexStageInfo, fragmentStageInfo};

    VkVertexInputBindingDescription bindingDescription{getBindingDescription()};
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions{getAttributeDescriptions()};


	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();





	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;


	VkExtent2D extent{device->width, device->height};

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(extent.width);
	viewport.height = static_cast<float>(extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = {0, 0};
	scissor.extent = extent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;


	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;


	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;


	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;

	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = pipeline.pipelineLayout;
	pipelineInfo.renderPass = pipeline.renderPass;
	pipelineInfo.subpass = 0;

	checkVulkanError(vkCreateGraphicsPipelines(device->logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline.pipeline), 
				 	 "GulgEngine can't create VkRenderPass.");
}


void createFramebuffers(std::shared_ptr<Device> device, Pipeline &pipeline) {

	for (size_t i{0}; i < device->imageViews.size(); i++) {

	    VkImageView attachments[] = { device->imageViews[i] };

	    VkFramebufferCreateInfo framebufferInfo = {};
	    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	    framebufferInfo.renderPass = pipeline.renderPass;
	    framebufferInfo.attachmentCount = 1;
	    framebufferInfo.pAttachments = attachments;
	    framebufferInfo.width = device->width;
	    framebufferInfo.height = device->height;
	    framebufferInfo.layers = 1;

	    VkFramebuffer newFramebuffer;

	    checkVulkanError(vkCreateFramebuffer(device->logicalDevice, &framebufferInfo, nullptr, &newFramebuffer), 
	    				 "GulgEngine can't create VkFramebuffer.");

	    pipeline.framebuffers.emplace_back(newFramebuffer);
	}
}


std::vector<char> readFile(const std::string &path) {

    std::ifstream file{path, std::ios::ate | std::ios::binary};

    if (!file.is_open()) { throw std::runtime_error("Shader load error: can't open file \"" +  path + "\"."); }

    size_t fileSize{static_cast<size_t>(file.tellg())};
	std::vector<char> result;
	result.resize(fileSize);

	file.seekg(0);
	file.read(result.data(), fileSize);
	file.close();

	return result;
}

VkShaderModule createShaderModule(std::shared_ptr<Device> device, const std::vector<char> &code) {

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	checkVulkanError(vkCreateShaderModule(device->logicalDevice, &createInfo, nullptr, &shaderModule), "GulgEngine can't create VkShaderModule.");

	return shaderModule;
}

VkVertexInputBindingDescription getBindingDescription() {

    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec3)*2;
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {

    std::vector<VkVertexInputAttributeDescription> descriptions;
    descriptions.resize(2);

    descriptions[0].binding = 0;
    descriptions[0].location = 0;
    descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    descriptions[0].offset = 0;

    descriptions[1].binding = 0;
    descriptions[1].location = 1;
    descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    descriptions[1].offset = sizeof(glm::vec3);


    return descriptions;
}









Pipeline createVulkanPipeline(std::shared_ptr<Device> device, const std::string vertexPath, const std::string fragmentPath) {

	Pipeline workingPipeline;

	try { loadShaderFromFile(device, workingPipeline.vertexModule, vertexPath); }
	catch(const std::exception &e) { throw e; }

	try { loadShaderFromFile(device, workingPipeline.fragmentModule, fragmentPath); }
	catch(const std::exception &e) { 

		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		throw e; 
	}

	try { createDescriptorSetLayout(device, workingPipeline); }

	catch(const std::exception &e) { 

		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.fragmentModule, nullptr);
		throw e; 
	}

	try { createPipelineLayout(device, workingPipeline); }
	catch(const std::exception &e) { 

		vkDestroyDescriptorSetLayout(device->logicalDevice, workingPipeline.descriptorSetLayout, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.fragmentModule, nullptr);
		throw e; 
	}

	try { createRenderPass(device, workingPipeline); }
	catch(const std::exception &e) { 

		vkDestroyPipelineLayout(device->logicalDevice, workingPipeline.pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device->logicalDevice, workingPipeline.descriptorSetLayout, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.fragmentModule, nullptr);
		throw e; 
	}

	try { createPipeline(device, workingPipeline); }
	catch(const std::exception &e) { 

		vkDestroyRenderPass(device->logicalDevice, workingPipeline.renderPass, nullptr);
		vkDestroyPipelineLayout(device->logicalDevice, workingPipeline.pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device->logicalDevice, workingPipeline.descriptorSetLayout, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.fragmentModule, nullptr);
		throw e; 
	}

	try { createFramebuffers(device, workingPipeline); }
	catch(const std::exception &e) { 

		vkDestroyPipeline(device->logicalDevice, workingPipeline.pipeline, nullptr);
		vkDestroyRenderPass(device->logicalDevice, workingPipeline.renderPass, nullptr);
		vkDestroyPipelineLayout(device->logicalDevice, workingPipeline.pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device->logicalDevice, workingPipeline.descriptorSetLayout, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, workingPipeline.fragmentModule, nullptr);
		throw e; 
	}

	fillSubmitInfos(device, workingPipeline);

	return std::move(workingPipeline);
}


void fillSubmitInfos(std::shared_ptr<Device> device, Pipeline &pipeline) {

	pipeline.submitInfo = {};
	pipeline.submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	pipeline.submitInfo.commandBufferCount = 1;

	pipeline.submitInfo.pWaitSemaphores = &device->readyForGraphics;
	pipeline.submitInfo.waitSemaphoreCount = 1;

	pipeline.submitInfo.pSignalSemaphores = &device->readyForPresent;
	pipeline.submitInfo.signalSemaphoreCount = 1;

	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	pipeline.submitInfo.pWaitDstStageMask = waitStages;

}