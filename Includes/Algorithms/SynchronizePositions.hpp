#ifndef SYNCHRONIZE_POSITION_HPP
#define SYNCHRONIZE_POSITION_HPP

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/Graphics/CircleShape.hpp"
#include "Components/Physics/Hitbox.hpp"

namespace Gg {

namespace Algorithm {

class SynchronizePositions: public AbstractAlgorithm {

	public:

		SynchronizePositions(GulgEngine &gulgEngine, const unsigned int pixelInMeter);
		virtual ~SynchronizePositions();

		void apply();

	private:

		const unsigned int m_pixelPerMeter;
};

}}

#endif