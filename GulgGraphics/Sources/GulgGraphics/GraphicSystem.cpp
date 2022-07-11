#include "GulgGraphics/GraphicSystem.hpp"

namespace Gg {

namespace System {


GraphicSystem::GraphicSystem(sf::RenderTarget &renderTarget): 
	m_systemSignature{ComponentSignatureKeeper::getSignature(Component::Type::SpriteComponent)},
	m_renderTarget{renderTarget}
	{}


void GraphicSystem::update(const double deltaTime) {

	m_renderTarget.clear(sf::Color::Black);

	for(const Entity currentEntity: m_entities) {

		//m_renderTarget.draw();
	}

	//m_renderTarget.display();

}

}

}
