#include "GulgGraphics/Components/Sprite.hpp"

namespace Gg {

namespace Component {

Sprite::Sprite() {}


Sprite::Sprite(glm::vec2 position, std::string texturePath) {

	m_texture.loadFromFile(texturePath);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position.x, position.y);
}


//TODO
std::shared_ptr<AbstractComponent> Sprite::clone() const { return nullptr; }


void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_sprite, states); }   

}

}