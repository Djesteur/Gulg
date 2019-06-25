#ifndef BASIC_COMPONENTs_HPP
#define BASIC_COMPONENTs_HPP

#include "Components/Component.hpp"

namespace Gg {

struct BooleanComponent: public Component {

	BooleanComponent(): value{false} {}

	BooleanComponent(const bool val): value{val} {}

	virtual std::shared_ptr<Component> clone() const { return std::static_pointer_cast<Component>(std::make_shared<BooleanComponent>(*this)); }

	bool value;          
};

}

#endif