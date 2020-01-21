#include "Algorithms/Graphics/DrawSprite.hpp"

namespace Gg {

namespace Algorithm {

DrawSprite::DrawSprite(sf::RenderTarget &renderTarget, 
									const std::string componentName,
										 GulgEngine &gulgEngine): 

	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawSprite::~DrawSprite() {}

void DrawSprite::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::Sprite> currentSpriteComponent{ 
			std::static_pointer_cast<Component::Sprite>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentSpriteComponent->sprite);
	}
}

}}