#ifndef COLLISION_RESOLUTION_HPP
#define COLLISION_RESOLUTION_HPP

#include "Algorithms/Algorithm.hpp"
#include "Algorithms/Physics/CollisionDeclarations.hpp"

#include "Components/Physics/Hitbox.hpp"

#include "Mathematics/Basics.hpp"

namespace Gg {

namespace Algorithm {

class CollisionResolution: public AbstractAlgorithm {

	public:

		CollisionResolution(GulgEngine &gulgEngine, std::vector<Collision> &collisionsToResolve);
		
		virtual ~CollisionResolution(); 

		void apply();

	private:

		std::vector<Collision> &m_collisionsToResolve;
		std::map<Entity, Component::Vector2D> m_finalVector;
};

}}

#endif