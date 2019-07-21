#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Components/Component.hpp"

namespace Gg {

struct SpriteComponent: public AbstractComponent {

	public:

		SpriteComponent() {}
		SpriteComponent(const SpriteComponent &spriteComponent): sprite{spriteComponent.sprite} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<SpriteComponent>(*this)); }

		sf::Sprite sprite;             
};

}

#endif