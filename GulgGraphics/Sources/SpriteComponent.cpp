#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(SpriteComponent toCopy) {}


std::shared_ptr<AbstractComponent> SpriteComponent::clone() const { return std::make_shared<SpriteComponent>(this); }