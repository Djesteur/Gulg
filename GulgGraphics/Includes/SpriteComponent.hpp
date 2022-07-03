#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

class SpriteComponent: AbstractComponent {

	public:

		SpriteComponent() {}
		SpriteComponent(SpriteComponent toCopy);

		virtual std::shared_ptr<AbstractComponent> clone() const; 
		virtual Type getType() const;


	protected:

		Type m_componentType;                  
};

}}

#endif