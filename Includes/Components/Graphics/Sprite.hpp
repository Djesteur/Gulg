#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Sprite: public AbstractComponent {

	public:

		Sprite() {}
		Sprite(const Sprite &spriteComponent): sprite{spriteComponent.sprite} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Sprite>(*this)); }

		sf::Sprite sprite;             
};

}}

#endif