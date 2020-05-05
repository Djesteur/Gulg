#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <vector>

#include "Vulkan/VulkanDeclaration.hpp"
#include "Vulkan/VulkanDevice.hpp"
#include "Vulkan/VulkanPipeline.hpp"

#include "Components/Component.hpp"
#include "Components/Mesh.hpp"

namespace Gg {

namespace Component {

class MeshRenderer: public AbstractComponent {

	public:

		MeshRenderer(std::shared_ptr<Device> device);
		MeshRenderer(std::shared_ptr<Device> device, const Mesh &mesh);

		MeshRenderer(const MeshRenderer &renderer);   //Not implemented yet
		void operator=(const MeshRenderer &renderer); //Not implemented yet

		virtual std::shared_ptr<AbstractComponent> clone() const; //Not implemented yet 

		~MeshRenderer();

		void loadFromMesh(const Mesh &mesh);

		void draw();

		void clean();

		VkBuffer m_verticesBuffer;
		VkBuffer m_indexBuffer;
		size_t m_nbIndices;

	private:
		
		void createCommandBuffers();


		std::shared_ptr<Device> m_device;

		bool m_wellInitialized;

		std::vector<VkCommandBuffer> m_commandBuffers;
		
		VkDeviceMemory m_verticesBufferMemory;
		VkDeviceMemory m_indexBufferMemory;

		Pipeline m_pipeline;
};

}}


#endif