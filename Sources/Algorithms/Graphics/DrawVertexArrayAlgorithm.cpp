#include "Algorithms/Graphics/DrawVertexArrayAlgorithm.hpp"

namespace Gg {

DrawVertexArrayAlgorithm::DrawVertexArrayAlgorithm(sf::RenderTarget &renderTarget, 
										 		  const std::string componentName, 
										 		  GulgEngine &gulgEngine): 
	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawVertexArrayAlgorithm::~DrawVertexArrayAlgorithm() {}

void DrawVertexArrayAlgorithm::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<VertexArrayComponent> currentSpriteComponent{ 
			std::static_pointer_cast<VertexArrayComponent>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentSpriteComponent->vertexArray, currentSpriteComponent->texture); 
	}
}

}