#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Component.hpp"

namespace Gg {

class SpriteComponent: public Component {

	public:

		SpriteComponent();
		SpriteComponent(const SpriteComponent &spriteComponent);

		sf::Sprite& spriteAcces();

		virtual std::shared_ptr<Component> clone() const;

	private:

		sf::Sprite m_sprite;             
};

}

#endif