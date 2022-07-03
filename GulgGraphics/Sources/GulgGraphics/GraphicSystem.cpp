#include "GulgGraphics/GraphicSystem.hpp"

namespace Gg {

namespace System {


GraphicSystem::GraphicSystem(): m_systemSignature{ComponentSignatureKeeper::getSignature(Component::Type::SpriteComponent)} {}


void GraphicSystem::update(const double deltaTime) {

}

}

}