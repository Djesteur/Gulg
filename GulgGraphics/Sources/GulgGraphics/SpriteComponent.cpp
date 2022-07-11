#include "GulgGraphics/SpriteComponent.hpp"

namespace Gg {

namespace Component {


SpriteComponent::SpriteComponent(sf::Vector2f position, std::string texturePath): AbstractComponent{Type::SpriteComponent} {

	m_texture.loadFromFile(texturePath);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}


std::shared_ptr<AbstractComponent> SpriteComponent::clone() const { return nullptr; }


void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_sprite, states); }   

}

}