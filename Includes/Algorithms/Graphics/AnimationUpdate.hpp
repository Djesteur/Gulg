#ifndef ANIMATION_UPDATE_HPP
#define ANIMATION_UPDATE_HPP

#include <chrono>
#include <ctime>

#include "Algorithms/SpecializedAlgorithm.hpp"

#include "Components/Graphics/AnimationSet.hpp"
#include "Components/BasicComponents.hpp"

namespace Gg {

namespace Algorithm {

class AnimationUpdate: public SpecializedAlgorithm {

	public:

		AnimationUpdate(const std::string componentName, GulgEngine &gulgEngine);
		
		virtual ~AnimationUpdate(); 

		void resetTime();

		void apply();

	protected:

		std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
};

}}

#endif