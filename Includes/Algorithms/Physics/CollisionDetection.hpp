#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include "Algorithms/Algorithm.hpp"
#include "Algorithms/Physics/CollisionDeclarations.hpp"

#include "Components/Physics/Hitbox.hpp"

#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Algorithm {

class CollisionDetection: public AbstractAlgorithm {

	public:

		CollisionDetection(GulgEngine &gulgEngine, std::vector<Collision> &collisionsToResolve);
		
		virtual ~CollisionDetection(); 

		void apply();

	private:

		void bothCircleCollision(const Entity firstEntity, Entity secondEntity);

		void convexAndCircle(const Entity convexEntity, Entity circleEntity);

		std::vector<Collision> &m_collisionsToResolve;
};

}}

#endif