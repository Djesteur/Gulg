#include "GulgGraphics/GraphicSystem.hpp"

namespace Gg {

namespace System {


GraphicSystem::GraphicSystem(ComponentKeeper &keeper, sf::RenderWindow &window): 
	AbstractSystem{keeper, ComponentSignatureKeeper::getSignature(Component::Type::SpriteComponent)},
	m_renderWindow{window}
	{}


void GraphicSystem::update(const double deltaTime) {

	m_renderWindow.clear(sf::Color{165, 80, 54});

	for(const Entity currentEntity: m_entities) { 

		m_renderWindow.draw(*m_componentKeeper.getComponent<Component::SpriteComponent>(currentEntity));
	}

	m_renderWindow.display();

}

}

}
