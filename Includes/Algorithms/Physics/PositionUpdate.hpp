#ifndef POSITION_UPDATE_HPP
#define POSITION_UPDATE_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"

namespace Gg {

namespace Algorithm {

class PositionUpdate: public AbstractAlgorithm {

	public:

		PositionUpdate(GulgEngine &gulgEngine);
		
		virtual ~PositionUpdate(); 

		void apply();
		void apply(const long unsigned int elapsedTime);
};

}}

#endif