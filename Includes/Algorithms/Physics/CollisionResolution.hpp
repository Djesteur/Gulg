#ifndef COLLISION_RESOLUTION_HPP
#define COLLISION_RESOLUTION_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/Physics/Hitbox.hpp"

#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Algorithm {

class CollisionResolution: public AbstractAlgorithm {

	public:

		CollisionResolution(GulgEngine &gulgEngine, std::vector<std::pair<Entity, Entity>> &collisionsToResolve);
		
		virtual ~CollisionResolution(); 

		void apply();

	private:

		std::vector<std::pair<Entity, Entity>> &m_collisionsToResolve;
};

}}

#endif