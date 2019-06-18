#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Components/Component.hpp"

namespace Gg {

struct SpriteComponent: public Component {

	public:

		SpriteComponent() {}
		SpriteComponent(const SpriteComponent &spriteComponent): sprite{spriteComponent.sprite} {}

		virtual std::shared_ptr<Component> clone() const { return std::static_pointer_cast<Component>(std::make_shared<SpriteComponent>(*this)); }

		sf::Sprite sprite;             
};

}

#endif