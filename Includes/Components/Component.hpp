#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "GulgEngine/GulgDeclarations.hpp"

namespace Gg {

struct AbstractComponent {

	public:

		AbstractComponent() {}

		virtual std::shared_ptr<AbstractComponent> clone() const = 0;                   
};

}

#endif