#ifndef BASIC_COMPONENTs_HPP
#define BASIC_COMPONENTs_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Boolean: public AbstractComponent {

	Boolean(): value{false} {}

	Boolean(const bool val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Boolean>(*this)); }

	bool value;          
};

struct EntityComponent: public AbstractComponent {

	EntityComponent(): value{0} {}

	EntityComponent(const Entity val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<EntityComponent>(*this)); }

	Entity value;          
};

struct String: public AbstractComponent {

	String(): value{""} {}

	String(const std::string val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<String>(*this)); }

	std::string value;          
};

struct Vector2D: public AbstractComponent {

	Vector2D(): value{0.f, 0.f} {}

	Vector2D(const Vector2D &vec): value{vec.value} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Vector2D>(*this)); }

	sf::Vector2f value;          
};

}}

#endif