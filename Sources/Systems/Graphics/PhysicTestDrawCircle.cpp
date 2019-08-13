#include "Systems/Graphics/PhysicTestDrawCircle.hpp"

PhysicTestDrawCircle::PhysicTestDrawCircle(sf::RenderTarget &m_renderTarget, Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::DrawCircleShape>(m_renderTarget, std::string{"GraphicHitbox"}, gulgEngine));
}

PhysicTestDrawCircle::~PhysicTestDrawCircle() {}