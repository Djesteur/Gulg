#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "Systems/System.hpp"
#include "Vulkan/VulkanDevice.hpp"
#include "Components/MeshRenderer.hpp"

namespace Gg {

namespace Systems {

class RenderSystem: public AbstractSystem {

	public:

		RenderSystem(GulgEngine &gulgEngine, std::shared_ptr<Device> device);

		virtual ~RenderSystem(); 

		virtual void apply();

	private:

		std::shared_ptr<Device> m_device;
};

}}

#endif