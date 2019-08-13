#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <string>

#include "Components/Component.hpp"
#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Component {

struct AbstractHitbox: public AbstractComponent {

	AbstractHitbox(): centerPosition{0.f, 0.f} {}
	AbstractHitbox(const Vector2D &center): centerPosition{center} {}

	virtual std::shared_ptr<AbstractComponent> clone() const = 0;
	virtual bool pointIsInside(Vector2D &pointPosition) const = 0;

	Vector2D centerPosition;
	
};

struct CircleHitbox: public AbstractHitbox {

	CircleHitbox(): AbstractHitbox{} {}
	CircleHitbox(const Vector2D &center, float newRadius = 1): 
		AbstractHitbox{center},
		radius{newRadius} {}

	CircleHitbox(const CircleHitbox &circle):
		AbstractHitbox{circle.centerPosition}, 
		radius{circle.radius} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<CircleHitbox>(*this)); }

	virtual bool pointIsInside(Vector2D &pointPosition) const {

		if(Maths::distance(centerPosition, pointPosition) > radius) { return false; }
		return true;
	}

	float radius;
};

}}

#endif