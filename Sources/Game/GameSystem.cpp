#include "Game/GameSystem.hpp"

namespace Gg {

GameSystem::GameSystem(EntitySignatureKeeper &entitySignatureKeeper, 
					   SignatureLoader &signatureLoader,
					   ComponentKeeper &componentKeeper): System{entitySignatureKeeper, signatureLoader, componentKeeper} {


	m_algorithms.emplace_back(std::make_unique<TimerAlgorithm>(signatureLoader, componentKeeper));
}

GameSystem::~GameSystem() {}

}