#include "Systems/Physics/Physic.hpp"

namespace Gg {

namespace Systems {

Physic::Physic(GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Algorithm::PositionUpdate>(gulgEngine));
	m_algorithms.emplace_back(std::make_unique<Algorithm::CollisionDetection>(gulgEngine, m_collisionsToResolve));
	m_algorithms.emplace_back(std::make_unique<Algorithm::CollisionResolution>(gulgEngine, m_collisionsToResolve));

	m_lastTimePoint = std::chrono::steady_clock::now();
}

Physic::~Physic() {}

void Physic::resetTime() { m_lastTimePoint = std::chrono::steady_clock::now(); }

void Physic::applyAlgorithms() {

	std::chrono::time_point<std::chrono::steady_clock> nowTimePoint{std::chrono::steady_clock::now()};
	const long int elapsedMicroseconds{std::chrono::duration_cast<std::chrono::microseconds>(nowTimePoint - m_lastTimePoint).count()};
	m_lastTimePoint = nowTimePoint;
	m_algorithms[0]->apply(elapsedMicroseconds);
	m_algorithms[1]->apply();
	m_algorithms[2]->apply();
}

}}