#ifndef TIMER_UPDATE_ALGORITHM_HPP
#define TIMER_UPDATE_ALGORITHM_HPP

#include <chrono>
#include <ctime>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Game/TimerComponent.hpp"

namespace Gg {

class TimerUpdateAlgorithm: public SpecializedAlgorithm {

	public:

		TimerUpdateAlgorithm(const std::string componentName, GulgEngine &gulgEngine);
		virtual ~TimerUpdateAlgorithm();

		void resetTime();

		void apply(); 

	protected:

		std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
};

}

#endif