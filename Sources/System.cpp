#include "System.hpp"

namespace Gg {

System::System(EntitySignatureKeeper &entitySignatureKeeper, SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper): 
	m_entitySignatureKeeper{entitySignatureKeeper} {}

System::~System() {}

void System::addEntity(const Entity newEntity) {

	for(std::unique_ptr<Algorithm> &currentAlgo: m_algorithms) {

		if((m_entitySignatureKeeper.getSignature(newEntity) & currentAlgo->getSignature()) == currentAlgo->getSignature()) {

			currentAlgo->addEntity(newEntity);
		}
	}
}

void System::deleteEntity(const Entity newEntity) {

	for(std::unique_ptr<Algorithm> &currentAlgo: m_algorithms) { currentAlgo->deleteEntity(newEntity); }
}

void System::applyAlgorithms() {

	for(std::unique_ptr<Algorithm> &currentAlgo: m_algorithms) { currentAlgo->apply(); }
}

}