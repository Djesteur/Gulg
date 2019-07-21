#ifndef BASIC_COMPONENTs_HPP
#define BASIC_COMPONENTs_HPP

#include <string>

#include "Components/Component.hpp"

namespace Gg {

struct BooleanComponent: public AbstractComponent {

	BooleanComponent(): value{false} {}

	BooleanComponent(const bool val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<BooleanComponent>(*this)); }

	bool value;          
};

struct EntityComponent: public AbstractComponent {

	EntityComponent(): value{0} {}

	EntityComponent(const Entity val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<EntityComponent>(*this)); }

	Entity value;          
};

struct StringComponent: public AbstractComponent {

	StringComponent(): value{""} {}

	StringComponent(const std::string val): value{val} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<StringComponent>(*this)); }

	std::string value;          
};

}

#endif