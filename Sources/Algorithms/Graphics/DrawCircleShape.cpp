#include "Algorithms/Graphics/DrawCircleShape.hpp"

namespace Gg {

namespace Algorithm {

DrawCircleShape::DrawCircleShape(sf::RenderTarget &renderTarget, 
									const std::string componentName,
										 GulgEngine &gulgEngine): 

	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawCircleShape::~DrawCircleShape() {}

void DrawCircleShape::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::CircleShape> currentSpriteComponent{ 
			std::static_pointer_cast<Component::CircleShape>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentSpriteComponent->circle);
	}
}

}}