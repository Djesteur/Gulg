#include "Algorithms/Graphics/DrawShape.hpp"

namespace Gg {

namespace Algorithm {

DrawShape::DrawShape(sf::RenderTarget &renderTarget, 
									const std::string componentName,
										 GulgEngine &gulgEngine): 

	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawShape::~DrawShape() {}

void DrawShape::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::Shape> currentSpriteComponent{ 
			std::static_pointer_cast<Component::Shape>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(*currentSpriteComponent->shape);
	}
}

}}