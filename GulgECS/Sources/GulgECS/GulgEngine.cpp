#include "GulgECS/GulgEngine.hpp"

namespace Gg {

GulgEngine::GulgEngine(const bool wantLogs, const std::string logFilePath) {

	if(wantLogs) {

		Logger::activateLogs();
		Logger::openFile(logFilePath);
	}

	ComponentSignatureKeeper::Init();
}

Entity GulgEngine::createEntity() {


	Entity newEntity{m_entityCreator.createEntity()};
	m_entitySignatureKeeper.addEntity(newEntity);
	m_componentKeeper.addEntity(newEntity);

	return newEntity;
}

void GulgEngine::deleteEntity(const Entity entity) {

	m_componentKeeper.removeEntity(entity);
	m_entitySignatureKeeper.removeEntity(entity);
	m_entityCreator.deleteEntity(entity);
}


Entity GulgEngine::cloneEntity(const Entity entityToClone) {

	Entity newEntity{createEntity()};
	m_entitySignatureKeeper.addToSignature(newEntity, m_entitySignatureKeeper.getSignature(entityToClone));
	m_componentKeeper.cloneEntity(entityToClone, newEntity);

	for(std::shared_ptr<AbstractSystem> currentSystem: m_systems) { 

		if(currentSystem->isInSystem(entityToClone)) { currentSystem->addEntity(newEntity, m_entitySignatureKeeper.getSignature(newEntity)); }

	 }

	return newEntity;
}


void GulgEngine::deleteComponent(const Entity entity, const Component::Type type) {

	if(m_componentKeeper.entityHasComponent(entity, type)) {

		m_componentKeeper.deleteComponent(entity, type);
		m_entitySignatureKeeper.removeFromSignature(entity, ComponentSignatureKeeper::getSignature(type));
	}	

	for(std::shared_ptr<AbstractSystem> currentSystem: m_systems) { currentSystem->entitySignatureChanged(entity, m_entitySignatureKeeper.getSignature(entity)); }
}

bool GulgEngine::entityHasComponent(const Entity entity, const Component::Type type) {

	return m_componentKeeper.entityHasComponent(entity, type);
}

std::shared_ptr<Component::AbstractComponent> GulgEngine::getComponent(const Entity entity, const Component::Type type) { return m_componentKeeper.getComponent(entity, type); }

}