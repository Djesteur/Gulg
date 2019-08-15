#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/Physics/Hitbox.hpp"

#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Algorithm {

class CollisionDetection: public AbstractAlgorithm {

	public:

		CollisionDetection(GulgEngine &gulgEngine, std::vector<std::pair<Entity, Entity>> &collisionsToResolve);
		
		virtual ~CollisionDetection(); 

		void apply();

		std::vector<std::pair<Entity, Entity>> getCollisionsToResolve() const;

	private:

		bool bothCircleCollision(std::shared_ptr<Component::CircleHitbox> firstHitbox,
								 std::shared_ptr<Component::CircleHitbox> secondHitbox) const;

		bool convexAndCircle(std::shared_ptr<Component::ConvexHitbox> convexHitbox,
						     std::shared_ptr<Component::CircleHitbox> circleHitbox) const;

		std::vector<std::pair<Entity, Entity>> &m_collisionsToResolve;
};

}}

#endif