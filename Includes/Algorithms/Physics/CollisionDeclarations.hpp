#ifndef COLLISION_DECLARATIONS_HPP
#define COLLISION_DECLARATIONS_HPP

#include "Components/BasicComponents.hpp"

namespace Gg {

	struct Collision {

		Entity firstEntity, secondEntity;
		Component::Vector2D collisionPoint;
		Component::Vector2D firstDirection, secondDirection;
		float missingDistanceFirst, missingDistanceSecond;

	};

}

#endif