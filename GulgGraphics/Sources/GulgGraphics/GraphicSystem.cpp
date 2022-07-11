#include "GulgGraphics/GraphicSystem.hpp"

namespace Gg {

namespace System {


GraphicSystem::GraphicSystem(GulgEngine &engine, sf::RenderWindow &renderWindow): 
	AbstractSystem{engine, ComponentSignatureKeeper::getSignature(Component::Type::SpriteComponent)},
	m_renderWindow{renderWindow}
	{}


void GraphicSystem::update(const double deltaTime) {

	m_renderWindow.clear(sf::Color{165, 80, 54});

	for(const Entity currentEntity: m_entities) { 

		m_renderWindow.draw(*std::static_pointer_cast<Component::SpriteComponent>(m_gulgEngine.getComponent(currentEntity, Component::Type::SpriteComponent))); 
	}

	m_renderWindow.display();

}

}

}
