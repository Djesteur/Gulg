#include "Systems/RenderSystem.hpp"
#include <iostream>

namespace Gg {

namespace Systems {

RenderSystem::RenderSystem(GulgEngine &gulgEngine, std::shared_ptr<Device> device):
	AbstractSystem{gulgEngine, ComponentType::MainMeshRenderer},
	m_device{device} { }

RenderSystem::~RenderSystem() {}

void RenderSystem::apply() {

	checkVulkanError(vkAcquireNextImageKHR(m_device->logicalDevice, m_device->swapChain, UINT64_MAX, m_device->readyForGraphics, 
												   VK_NULL_HANDLE, &m_device->currentImageIndex), 
					"GulgEngine can't acquire next image.");

	for(Entity currentEntity: m_entities) {

		m_gulgEngine.getComponent<Component::MeshRenderer>(currentEntity, ComponentType::MainMeshRenderer)->draw();
	}
			
			
	checkVulkanError(vkQueuePresentKHR(m_device->presentQueue, &m_device->presentInfo), "GulgEngine can't present draw.");
}

}}