#ifndef CIRCLE_SHAPE_COMPONENT_HPP
#define CIRCLE_SHAPE_COMPONENT_HPP

#include <SFML/Graphics/CircleShape.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct CircleShape: public AbstractComponent {

	public:

		CircleShape(): texture{nullptr} {}
		CircleShape(const CircleShape &component): 
			circle{component.circle},
			texture{component.texture} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<CircleShape>(*this)); }

		sf::CircleShape circle;
		sf::Texture *texture;           
};

}}

#endif