#include "GulgPhysics/Components/Hitbox2D.hpp"

namespace Gg {

namespace Component {

Hitbox2D::Hitbox2D() {}

Hitbox2D::Hitbox2D(const sf::Vector2f &vertexShift, const Gg::Shape2D &convexShape, const testConvexity) { Hitbox2D(vertexShift, {convexShape}, testConvexity); }

Hitbox2D::Hitbox2D(const sf::Vector2f &vertexShift, const std::vector<Gg::Shape2D> &convexShapes, const testConvexity):
	m_vertexShift{vertexShift},
	m_shapes{convexShapes} {

	//Todo: test convexity



}


std::shared_ptr<AbstractComponent> Hitbox2D::clone() const { return nullptr; }


bool Hitbox2D::isInside(const sf::Vector2f &hitboxPosition, const sf::Vector2f &pointToTest) {

	//TODO
	return false;
}

}

}