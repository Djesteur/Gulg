#ifndef ABSTRACT_COMPONENT_HPP
#define ABSTRACT_COMPONENT_HPP

#include <memory>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

namespace Gg {

namespace Component {

class AbstractComponent {

	public:

		AbstractComponent(const Type componentType);

		virtual std::shared_ptr<AbstractComponent> clone() const = 0; 
		virtual Type getType() const;


	protected:

		const Type m_componentType;        
};

}}

#endif