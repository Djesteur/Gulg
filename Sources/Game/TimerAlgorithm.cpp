#include "Game/TimerAlgorithm.hpp"

namespace Gg {

TimerAlgorithm::TimerAlgorithm(SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper): 
	Algorithm{componentKeeper, signatureLoader} {

		m_signature = signatureLoader.getSignature("SpawnTimer");
		m_lastTimePoint = std::chrono::steady_clock::now();
	}

TimerAlgorithm::~TimerAlgorithm() {}

void TimerAlgorithm::resetTime() { m_lastTimePoint = std::chrono::steady_clock::now(); }

void TimerAlgorithm::apply() {

	std::chrono::time_point<std::chrono::steady_clock> nowTimePoint{std::chrono::steady_clock::now()};

	const long int elapsedMicroseconds{std::chrono::duration_cast<std::chrono::microseconds>(nowTimePoint - m_lastTimePoint).count()};

	m_lastTimePoint = nowTimePoint;

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<TimerComponent> currentTimerComponent{ 
			std::static_pointer_cast<TimerComponent>(m_componentKeeper.getComponent(currentEntity, "SpawnTimer"))
		};


		currentTimerComponent->localElapsedMicroseconds += elapsedMicroseconds;

		while(currentTimerComponent->localElapsedMicroseconds >= currentTimerComponent->timeLimit) {

			std::cout << "Timer trigger, entity " << currentEntity << std::endl;

			currentTimerComponent->localElapsedMicroseconds -= currentTimerComponent->timeLimit;
			currentTimerComponent->nbTrigger++;
		}
	}
}

}