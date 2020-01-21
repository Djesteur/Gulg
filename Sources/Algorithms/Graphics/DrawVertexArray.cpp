#include "Algorithms/Graphics/DrawVertexArray.hpp"

namespace Gg {
namespace Algorithm {

DrawVertexArray::DrawVertexArray(sf::RenderTarget &renderTarget, 
										 		  const std::string componentName, 
										 		  GulgEngine &gulgEngine): 
	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawVertexArray::~DrawVertexArray() {}

void DrawVertexArray::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::VertexArray> currentSpriteComponent{ 
			std::static_pointer_cast<Component::VertexArray>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentSpriteComponent->vertexArray, currentSpriteComponent->texture); 
	}
}

}}