#ifndef PHYSIC_TEST_HPP
#define PHYSIC_TEST_HPP

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/SynchronizePositions.hpp"

namespace Gg {

namespace Systems {

class PhysicTest: public Gg::Systems::AbstractSystem {

	public:

		PhysicTest(Gg::GulgEngine &gulgEngine);
		
		virtual ~PhysicTest(); 

	private:

};

}}


#endif