#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <string>

#include "Components/Component.hpp"
#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Component {

struct AbstractHitbox: public AbstractComponent {

	AbstractHitbox(): centerPosition{0.f, 0.f} {}
	AbstractHitbox(const Vector2D &center): 
		centerPosition{center} {}

	virtual std::shared_ptr<AbstractComponent> clone() const = 0;
	virtual bool pointIsInside(Vector2D &pointPosition) const = 0;
	virtual bool isCircle() const = 0;

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

	virtual bool isCircle() const { return true; }

	float radius;
};

struct ConvexHitbox: public AbstractHitbox {

	ConvexHitbox(): AbstractHitbox{} {}
	ConvexHitbox(const Vector2D &center): 
		AbstractHitbox{center} {}

	ConvexHitbox(const ConvexHitbox &convex):
		AbstractHitbox{convex.centerPosition} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<ConvexHitbox>(*this)); }

	virtual bool pointIsInside(Vector2D &pointPosition) const {

		std::vector<Vector2D> testShape{absolutePoints};
		testShape.emplace_back(absolutePoints[0]);

		unsigned int direction1{0}, direction2{0};
		Vector2D v1, v2;

		for(unsigned int i{0}; i < testShape.size()-1; i++) {

			v1 = Maths::vectorFromPoints(absolutePoints[i].value, absolutePoints[i+1].value);
			v2 = Maths::vectorFromPoints(absolutePoints[i+1].value, pointPosition.value);

			if(Maths::determinant(v1.value, v2.value) <= 0) { direction1++; }
			else { direction2++; }
		}

		if(direction1 == 0 || direction2 == 0) { return true; }
		return false;
	}

	virtual bool isCircle() const { return false; }

	void setPosition(Vector2D newPosition) {

		centerPosition = newPosition;
		updatePoints();
	}

	void move(Vector2D movePosition) {

		centerPosition.value += movePosition.value;
		updatePoints();
	}

	void updatePoints() {

		for(unsigned int i{0}; i < absolutePoints.size(); i++) {

			absolutePoints[i].value = centerPosition.value + relativPoints[i].value;
		}
	}

	std::vector<Vector2D> relativPoints, absolutePoints; //Relativ to centerPosition
};

}}

#endif