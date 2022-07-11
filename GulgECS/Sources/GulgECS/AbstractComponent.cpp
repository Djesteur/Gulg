#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

	AbstractComponent::AbstractComponent(const Type componentType): m_componentType{componentType} {}

Type AbstractComponent::getType() const { return m_componentType; }

}

}

