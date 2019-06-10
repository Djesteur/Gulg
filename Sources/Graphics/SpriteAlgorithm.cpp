#include "Graphics/SpriteAlgorithm.hpp"

namespace Gg {

SpriteAlgorithm::SpriteAlgorithm(sf::RenderTarget &renderTarget, SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper): 
	Algorithm{componentKeeper, signatureLoader},
	m_renderTarget{renderTarget} {

	m_signature = signatureLoader.getSignature("MainSprite");
}

SpriteAlgorithm::~SpriteAlgorithm() {}

void SpriteAlgorithm::apply() {

	//std::cout << "nbEntity:" <<  m_entitiesToApply.size() << std::endl;

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<SpriteComponent> currentSpriteComponent{ 
			std::static_pointer_cast<SpriteComponent>(m_componentKeeper.getComponent(currentEntity, "MainSprite"))
		};

		m_renderTarget.draw(currentSpriteComponent->spriteAcces());
	}
}

}