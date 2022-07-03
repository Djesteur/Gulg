#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

class SpriteComponent: public AbstractComponent {

	public:

		SpriteComponent();

		virtual std::shared_ptr<AbstractComponent> clone() const; 


	protected:

		Type m_componentType;                  
};

}

}

#endif