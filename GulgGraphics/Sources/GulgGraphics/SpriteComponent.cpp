#include "GulgGraphics/SpriteComponent.hpp"

namespace Gg {

namespace Component {


SpriteComponent::SpriteComponent(): m_componentType{Type::SpriteComponent} {}


std::shared_ptr<AbstractComponent> SpriteComponent::clone() const { return nullptr; }

}

}