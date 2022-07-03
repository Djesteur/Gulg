#ifndef ABSTRACT_COMPONENT_HPP
#define ABSTRACT_COMPONENT_HPP

#include <memory>

#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

namespace Component {

class AbstractComponent {

	public:

		AbstractComponent() {}

		virtual std::shared_ptr<AbstractComponent> clone() const = 0; 
		Type getType() const;


	protected:

		Type m_componentType;                  
};

}}

#endif