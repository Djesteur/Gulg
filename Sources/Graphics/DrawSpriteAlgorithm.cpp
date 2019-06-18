#include "Graphics/DrawSpriteAlgorithm.hpp"

namespace Gg {

DrawSpriteAlgorithm::DrawSpriteAlgorithm(sf::RenderTarget &renderTarget, 
										 const std::string componentName,
										 ComponentKeeper &componentKeeper,
										 SignatureLoader &signatureLoader): 

	SpecializedAlgorithm{componentName, componentKeeper, signatureLoader},
	m_renderTarget{renderTarget} {}

DrawSpriteAlgorithm::~DrawSpriteAlgorithm() {}

void DrawSpriteAlgorithm::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<SpriteComponent> currentSpriteComponent{ 
			std::static_pointer_cast<SpriteComponent>(m_componentKeeper.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentSpriteComponent->sprite);
	}
}

}