#include "Systems/CharacterUpdate.hpp"

CharacterUpdate::CharacterUpdate(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::SynchronizePositions>(gulgEngine, 8));
	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::AnimationUpdate>("Animation", gulgEngine));
}

CharacterUpdate::~CharacterUpdate() {}
