#ifndef TIMER_ALGORITHM_HPP
#define TIMER_ALGORITHM_HPP

#include <chrono>
#include <ctime>

#include "Algorithm.hpp"
#include "Game/TimerComponent.hpp"

namespace Gg {

class TimerAlgorithm: public Algorithm {

	public:

		TimerAlgorithm(SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper);
		virtual ~TimerAlgorithm();

		void resetTime();

		void apply(); 

	protected:

		std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
};

}

#endif