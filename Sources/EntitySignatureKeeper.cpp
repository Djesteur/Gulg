#include "EntitySignatureKeeper.hpp"

namespace Gg {

EntitySignatureKeeper::EntitySignatureKeeper() {}


void EntitySignatureKeeper::addEntity(const Entity entity) {

	if(!entityExist(entity)) { m_signatures.insert(std::make_pair(entity, Signature{})); }
}

void EntitySignatureKeeper::deleteEntity(const Entity entity) {

	if(entityExist(entity)) { m_signatures.erase(m_signatures.find(entity)); }
}

bool EntitySignatureKeeper::entityExist(const Entity entity) const {

	if(m_signatures.find(entity) == m_signatures.end()) { return false; }
	return true;
}

void EntitySignatureKeeper::addToSignature(const Entity entity, const Signature signature) {

	if(entityExist(entity)) { m_signatures[entity] += signature; }
}

void EntitySignatureKeeper::deleteToSignature(const Entity entity, const Signature signature) {

	if(entityExist(entity)) { m_signatures[entity] -= signature; }
}

void EntitySignatureKeeper::cloneEntity(const Entity entityToClone, const Entity clone) {

	if(entityExist(entityToClone)) { 

		addEntity(clone);
		m_signatures[clone] = m_signatures[entityToClone]; 
	}
}
		
Signature EntitySignatureKeeper::getSignature(const Entity entity) const {

	if(entityExist(entity)) { return m_signatures.at(entity); }

	return Signature{};
}

}