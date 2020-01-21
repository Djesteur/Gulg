#include "Systems/Graphics/PhysicTestDraw.hpp"

PhysicTestDraw::PhysicTestDraw(sf::RenderTarget &m_renderTarget, Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::DrawShape>(m_renderTarget, std::string{"GraphicHitbox"}, gulgEngine));
}

PhysicTestDraw::~PhysicTestDraw() {}