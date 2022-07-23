#ifndef ABSTRACT_COMPONENT_HPP
#define ABSTRACT_COMPONENT_HPP

#include <memory>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

namespace Gg {

namespace Component {

/**
 * @brief      Parent class for all components used in Gulg.
 * @details Parent class for all components used in Gulg. The children must overload the clone function, and have a static function with the signature: Component::Type getType();
 *
 */

class AbstractComponent {

	public:

		/**
		 * @brief      Default constructor
		 */

		AbstractComponent();

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */

		virtual std::shared_ptr<AbstractComponent> clone() const = 0;
};

}}

#endif