#ifndef TIMER_UPDATE_HPP
#define TIMER_UPDATE_HPP

#include <chrono>
#include <ctime>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Game/Timer.hpp"

namespace Gg {

namespace Algorithm {

class TimerUpdate: public SpecializedAlgorithm {

	public:

		TimerUpdate(const std::string componentName, GulgEngine &gulgEngine);
		virtual ~TimerUpdate();

		void resetTime();

		void apply(); 

	protected:

		std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
};

}}

#endif