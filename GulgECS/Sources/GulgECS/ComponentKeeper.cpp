#include "GulgECS/ComponentKeeper.hpp"

#include <iostream>

namespace Gg {

ComponentKeeper::ComponentKeeper() {}

void ComponentKeeper::addEntity(const Entity newEntity) {

	if(!entityExist(newEntity)) { m_components.insert(std::make_pair(newEntity, std::map<Component::Type, std::shared_ptr<Component::AbstractComponent>>{})); }
}

void ComponentKeeper::removeEntity(const Entity currentEntity) {

	if(entityExist(currentEntity)) { m_components.erase(m_components.find(currentEntity)); }
}


void ComponentKeeper::deleteComponent(const Entity currentEntity, const Component::Type type) {

	if(entityHasComponent(currentEntity, type)) { //Also check if entity is existing

		m_components[currentEntity].erase(m_components[currentEntity].find(type));
	}
}

bool ComponentKeeper::entityExist(const Entity currentEntity) const {

	if(m_components.find(currentEntity) == m_components.end()) { return false; }
	return true;
}

bool ComponentKeeper::entityHasComponent(const Entity currentEntity, const Component::Type type) const {

	if(entityExist(currentEntity)) {

		if(m_components.at(currentEntity).find(type) != m_components.at(currentEntity).end()) { return true; }
	}

	return false;
}

void ComponentKeeper::cloneEntity(const Entity entityToClone, const Entity clone) {

	if(entityExist(entityToClone)) {

		addEntity(clone);

		for(std::pair<Component::Type, std::shared_ptr<Component::AbstractComponent>> currentComponent: m_components[entityToClone]) {

			m_components[clone].insert(std::make_pair(currentComponent.first, currentComponent.second->clone()));
		}
	}
}

 
std::shared_ptr<Component::AbstractComponent> ComponentKeeper::getComponent(const Entity currentEntity, const Component::Type type) const {

	if(entityHasComponent(currentEntity, type)) { return m_components.at(currentEntity).at(type); }

	throw std::runtime_error("Gulg error: asked for component " + std::to_string(static_cast<uint32_t>(type)) + " of entity " 
		+ std::to_string(currentEntity) + ", which doesn't exist.");

	return nullptr;
}

}

