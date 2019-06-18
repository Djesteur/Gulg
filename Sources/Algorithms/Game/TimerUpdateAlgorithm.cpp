#include "Algorithms/Game/TimerUpdateAlgorithm.hpp"

namespace Gg {

TimerUpdateAlgorithm::TimerUpdateAlgorithm(const std::string componentName, GulgEngine &gulgEngine): 
	SpecializedAlgorithm{componentName, gulgEngine} {

		m_lastTimePoint = std::chrono::steady_clock::now();
	}

TimerUpdateAlgorithm::~TimerUpdateAlgorithm() {}

void TimerUpdateAlgorithm::resetTime() { m_lastTimePoint = std::chrono::steady_clock::now(); }

void TimerUpdateAlgorithm::apply() {

	std::chrono::time_point<std::chrono::steady_clock> nowTimePoint{std::chrono::steady_clock::now()};

	const long int elapsedMicroseconds{std::chrono::duration_cast<std::chrono::microseconds>(nowTimePoint - m_lastTimePoint).count()};

	m_lastTimePoint = nowTimePoint;

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<TimerComponent> currentTimerComponent{ 
			std::static_pointer_cast<TimerComponent>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};


		currentTimerComponent->localElapsedMicroseconds += elapsedMicroseconds;

		while(currentTimerComponent->localElapsedMicroseconds >= currentTimerComponent->timeLimit) {

			currentTimerComponent->localElapsedMicroseconds -= currentTimerComponent->timeLimit;
			currentTimerComponent->nbTrigger++;
		}
	}
}

}