#include "GulgGraphics/Components/Sprite.hpp"

namespace Gg {

namespace Component {

Sprite::Sprite() {}


Sprite::Sprite(sf::Vector2f position, std::string texturePath) {

	m_texture.loadFromFile(texturePath);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}


//TODO
std::shared_ptr<AbstractComponent> Sprite::clone() const { return nullptr; }


void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_sprite, states); }   

}

}