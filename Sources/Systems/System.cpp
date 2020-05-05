#include "Systems/System.hpp"

namespace Gg {

namespace Systems {

AbstractSystem::AbstractSystem(GulgEngine &gulgEngine, const Signature signature): 
	m_gulgEngine{gulgEngine},
	m_systemSignature{signature} {}

AbstractSystem::~AbstractSystem() {}

void AbstractSystem::addEntity(const Entity entity) {

	if((m_gulgEngine.getEntitySignature(entity) & m_systemSignature) == m_systemSignature) { m_entities.emplace_back(entity); }
}

void AbstractSystem::deleteEntity(const Entity entity) {

	std::vector<Entity>::iterator findEntity{std::find(m_entities.begin(), m_entities.end(), entity)};

	if(findEntity != m_entities.end()) { m_entities.erase(findEntity); }
}


}}