#include "GulgEngine/GulgEngine.hpp"

namespace Gg {

GulgEngine::GulgEngine() {}

Entity GulgEngine::getNewEntity() {

	Entity newEntity{m_entityCreator.createEntity()};
	m_entitySignatureKeeper.addEntity(newEntity);
	m_componentKeeper.addEntity(newEntity);

	return newEntity;
}

void GulgEngine::deleteEntity(const Entity entity) {

	m_entityCreator.freeEntity(entity);
	m_entitySignatureKeeper.deleteEntity(entity);
	m_componentKeeper.deleteEntity(entity);
}

void GulgEngine::addComponentToEntity(const Entity entity, const ComponentType type, std::shared_ptr<Component::AbstractComponent> component) {

	m_componentKeeper.addComponent(entity, type, component);
	m_entitySignatureKeeper.addToSignature(entity, Signature{type});
}

void GulgEngine::deleteComponentToEntity(const Entity entity, const ComponentType type) {

	m_componentKeeper.deleteComponent(entity, type);
	m_entitySignatureKeeper.deleteToSignature(entity, Signature{type});
}

bool GulgEngine::entityHasComponent(const Entity entity, const ComponentType type) {

	return m_componentKeeper.entityHasComponent(entity, type);
}

Signature GulgEngine::getEntitySignature(const Entity entity) const {

	return m_entitySignatureKeeper.getSignature(entity);
}

std::shared_ptr<Component::AbstractComponent> GulgEngine::getComponent(const Entity entity, const ComponentType type) const {

	return m_componentKeeper.getComponent(entity, type);
}

Entity GulgEngine::cloneEntity(const Entity entityToClone) {

	Entity newEntity{getNewEntity()};
	m_entitySignatureKeeper.addToSignature(newEntity, m_entitySignatureKeeper.getSignature(entityToClone));
	m_componentKeeper.cloneEntity(entityToClone, newEntity);

	return newEntity;
}

}