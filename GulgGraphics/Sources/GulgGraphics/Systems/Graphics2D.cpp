#include "GulgGraphics/Systems/Graphics2D.hpp"

namespace Gg {

namespace System {


Graphics2D::Graphics2D(ComponentKeeper &keeper, sf::RenderWindow &window): 
	AbstractSystem{keeper, ComponentSignatureKeeper::getSignature<Component::Sprite>()},
	m_renderWindow{window}
	{}


void Graphics2D::update(const double deltaTime) {

	m_renderWindow.clear(sf::Color{165, 80, 54});

	for(const Entity currentEntity: m_entities) { 

		m_renderWindow.draw(*m_componentKeeper.getComponent<Component::Sprite>(currentEntity));
	}

	m_renderWindow.display();

}

}

}
