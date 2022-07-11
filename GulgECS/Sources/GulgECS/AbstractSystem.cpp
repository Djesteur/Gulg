#include "GulgECS/AbstractSystem.hpp"
#include "GulgECS/GulgEngine.hpp" 

namespace Gg {

namespace System {

AbstractSystem::AbstractSystem(GulgEngine &engine, const Signature systemSignature): 
	m_gulgEngine{engine},
	m_systemSignature{systemSignature} {}

AbstractSystem::~AbstractSystem() {}

void AbstractSystem::addEntity(const Entity entity, const Signature entitySignature) {

	if(entitySignature.containSignature(m_systemSignature)) { m_entities.emplace_back(entity); }
}

void AbstractSystem::deleteEntity(const Entity entity) {

	std::vector<Entity>::iterator findEntity{std::find(m_entities.begin(), m_entities.end(), entity)};

	if(findEntity != m_entities.end()) { m_entities.erase(findEntity); }
}

void AbstractSystem::entitySignatureChanged(const Entity entity, const Signature newSignature) {

	if(isInSystem(entity) && !newSignature.containSignature(m_systemSignature)) { deleteEntity(entity); }
}

bool AbstractSystem::isInSystem(const Entity entity) const { return std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end(); }

}}