#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "GulgDeclarations.hpp"

namespace Gg {

struct Component {

	public:

		Component() {}

		virtual std::shared_ptr<Component> clone() const = 0;                   
};

}

#endif