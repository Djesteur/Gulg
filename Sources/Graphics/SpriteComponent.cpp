#include "Graphics/SpriteComponent.hpp"

namespace Gg {

SpriteComponent::SpriteComponent() {}

SpriteComponent::SpriteComponent(const SpriteComponent &spriteComponent): m_sprite{spriteComponent.m_sprite} {}

sf::Sprite& SpriteComponent::spriteAcces() { return m_sprite; }

std::shared_ptr<Component> SpriteComponent::clone() const {

	return std::static_pointer_cast<Component>(std::make_shared<SpriteComponent>(*this));
}

}