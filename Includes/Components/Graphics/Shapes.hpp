#ifndef SHAPES_COMPONENT_HPP
#define SHAPES_COMPONENT_HPP

#include <memory>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Shape: public AbstractComponent {

	public:

		Shape(): 
			shape{nullptr},
			texture{nullptr} {}

		Shape(const Shape &component): 
			shape{nullptr},
			texture{component.texture} {}

		virtual std::shared_ptr<AbstractComponent> clone() const = 0;

		std::unique_ptr<sf::Shape> shape;
		sf::Texture *texture;         
};

struct CircleShape: public Shape {

	public:

		CircleShape(): Shape{} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<CircleShape>(*this)); }        
};

struct ConvexShape: public Shape {

	public:

		ConvexShape(): Shape{} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<ConvexShape>(*this)); }        
};

}}

#endif