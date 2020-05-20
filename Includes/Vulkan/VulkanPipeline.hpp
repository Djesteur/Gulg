#ifndef VULKAN_PIPELINE_HPP
#define VULKAN_PIPELINE_HPP

#include <set>
#include <fstream>
#include <sstream>

#include <Libraries/glm/glm.hpp>

#define GLFW_INCLUDE_VULKAN
#include <Libraries/GLFW/glfw3.h>

#include "Vulkan/VulkanDeclaration.hpp"
#include "Vulkan/VulkanDevice.hpp"

struct Pipeline {

	Pipeline() {}

	void clean(std::shared_ptr<Device> device) {

		for(VkFramebuffer currentFramebuffer: framebuffers) { vkDestroyFramebuffer(device->logicalDevice, currentFramebuffer, nullptr); }

		vkDestroyPipeline(device->logicalDevice, pipeline, nullptr);
		vkDestroyRenderPass(device->logicalDevice, renderPass, nullptr);
		vkDestroyPipelineLayout(device->logicalDevice, pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device->logicalDevice, descriptorSetLayout, nullptr);
		vkDestroyShaderModule(device->logicalDevice, vertexModule, nullptr);
		vkDestroyShaderModule(device->logicalDevice, fragmentModule, nullptr);
	}

	VkShaderModule vertexModule, fragmentModule;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;
	VkPipeline pipeline;

	std::vector<VkFramebuffer> framebuffers;

	VkSubmitInfo submitInfo;
};


Pipeline createVulkanPipeline(std::shared_ptr<Device> device, const std::string vertexPath, const std::string fragmentPath);

void fillSubmitInfos(std::shared_ptr<Device> device, Pipeline &pipeline);

#endif