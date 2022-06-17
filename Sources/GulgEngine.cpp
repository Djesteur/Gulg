#include "GulgEngine.hpp"

namespace Gg {

GulgEngine::GulgEngine(const bool wantLogs, const std::string logFilePath): m_componentCreator{m_componentSignatureKeeper} {

	if(wantLogs) {

		Logger::activateLogs();
		Logger::openFile(logFilePath);
	}
}

Entity GulgEngine::getNewEntity() {


	Entity newEntity{m_entityCreator.createEntity()};
	m_entitySignatureKeeper.addEntity(newEntity);
	m_componentKeeper.addEntity(newEntity);

	return newEntity;
}

void GulgEngine::deleteEntity(const Entity entity) {

	m_componentKeeper.deleteEntity(entity);
	m_entitySignatureKeeper.deleteEntity(entity);
	m_entityCreator.freeEntity(entity);

}



void GulgEngine::addComponentToEntity(const Entity entity, std::shared_ptr<Component::AbstractComponent> component) {

	if(!m_componentKeeper.entityHasComponent(entity, component->getType())) {

		m_componentKeeper.addComponent(entity, component);
		m_entitySignatureKeeper.addToSignature(entity, m_componentSignatureKeeper.getSignature(component->getType()));
	}
}

void GulgEngine::deleteComponentToEntity(const Entity entity, std::shared_ptr<Component::AbstractComponent> component) { deleteComponentToEntity(entity, component->getType()); }


void GulgEngine::deleteComponentToEntity(const Entity entity, const Component::Type type) {

	if(m_componentKeeper.entityHasComponent(entity, type)) {

		m_componentKeeper.deleteComponent(entity, type);
		m_entitySignatureKeeper.deleteToSignature(entity, m_componentSignatureKeeper.getSignature(type));
		
	}	

	for(System::AbstractSystem& currentSystem: m_systems) { currentSystem.entitySignatureChanged(entity, m_entitySignatureKeeper.getSignature(entity)); }
}

bool GulgEngine::entityHasComponent(const Entity entity, const Component::Type type) {

	return m_componentKeeper.entityHasComponent(entity, type);
}

Signature GulgEngine::getEntitySignature(const Entity entity) const { return m_entitySignatureKeeper.getSignature(entity); }

void GulgEngine::registerComponent(std::shared_ptr<Component::AbstractComponent> componentToRegister) { 

	m_componentCreator.registerComponent(componentToRegister); 
}

void GulgEngine::unregisterComponent(std::shared_ptr<Component::AbstractComponent> componentToUnregister) { 

	m_componentCreator.unregisterComponent(componentToUnregister); 
}


std::shared_ptr<Component::AbstractComponent> GulgEngine::createComponent(const Component::Type type) const { 

	return m_componentCreator.createComponent(type); 
}

std::shared_ptr<Component::AbstractComponent> GulgEngine::getComponent(const Entity entity, const Component::Type type) const {

	return m_componentKeeper.getComponent(entity, type);
}

Entity GulgEngine::cloneEntity(const Entity entityToClone) {

	Entity newEntity{getNewEntity()};
	m_entitySignatureKeeper.addToSignature(newEntity, m_entitySignatureKeeper.getSignature(entityToClone));
	m_componentKeeper.cloneEntity(entityToClone, newEntity);

	return newEntity;
}

void GulgEngine::addSystem(System::AbstractSystem& systemToAdd) { 

	m_systems.emplace_back(systemToAdd); 
}

void GulgEngine::deleteSystem(System::AbstractSystem& systemToDelete) { 

	size_t systemToDeleteIndex{0};
	bool foundSystemToDelete{false};

	for(size_t i{0}; i < m_systems.size(); i++) {

		if(std::addressof(m_systems[i].get()) == &systemToDelete) { 

			systemToDeleteIndex = i; 
			foundSystemToDelete = true;
		}
	}

	if(foundSystemToDelete) { 

		m_systems.erase(m_systems.begin() + systemToDeleteIndex); 
	}

}

}