#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <chrono>
#include <ctime>

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/Physics/CollisionDeclarations.hpp"
#include "Algorithms/Physics/PositionUpdate.hpp"
#include "Algorithms/Physics/CollisionDetection.hpp"
#include "Algorithms/Physics/CollisionResolution.hpp"

namespace Gg {

namespace Systems {

class Physic: public Gg::Systems::AbstractSystem {

	public:

		Physic(Gg::GulgEngine &gulgEngine);
		
		virtual ~Physic(); 

		void resetTime();

		virtual void applyAlgorithms();

	private:

		std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
		std::vector<Collision> m_collisionsToResolve;

};

}}


#endif