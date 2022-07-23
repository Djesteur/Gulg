#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

#include "GulgECS/GulgDeclarations.hpp"

#include "GulgECS/EntityCreator.hpp"
#include "GulgECS/EntitySignatureKeeper.hpp"
#include "GulgECS/ComponentKeeper.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/AbstractSystem.hpp"

#include "GulgECS/Logger.hpp"

using namespace Gg::Component;
using namespace Gg::System;

namespace Gg {

class GulgEngine {

	public:

		GulgEngine(const bool wantLogs = false, const std::string logFilePath = "LogFile.log");

		Entity createEntity();
		void deleteEntity(const Entity entity);
		Entity cloneEntity(const Entity entityToClone);

		template<ComponentConstraint T, typename... Args>
		std::shared_ptr<T> createComponent(const Entity entity, Args&&... args) {

			if(!m_componentKeeper.entityHasComponent<T>(entity)) {

				std::shared_ptr<T> newComponent = std::static_pointer_cast<T>(m_componentKeeper.createComponent<T>(entity, args...));
				m_entitySignatureKeeper.addToSignature(entity, ComponentSignatureKeeper::getSignature(T::getType()));

				return newComponent;
			}

			return std::static_pointer_cast<T>(m_componentKeeper.getComponent(entity, T::getType()));
		}


		template<ComponentConstraint T>
		void deleteComponent(const Entity entity) { deleteComponent(entity, T::getType()); }
		void deleteComponent(const Entity entity, const Type type);

		template<ComponentConstraint T>
		bool entityHasComponent(const Entity entity) { return entityHasComponent(entity, T::getType()); }
		bool entityHasComponent(const Entity entity, const Type type);

		template<ComponentConstraint T>
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity) { return getComponent(entity, T::getType()); }
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity, const Type type);


		template<SystemConstraint T, typename... Args>
		std::shared_ptr<T> createSystem(Args&&... args) {

			m_systems.emplace_back(std::make_shared<T>(m_componentKeeper, args...));
			return std::static_pointer_cast<T>(m_systems.back());
		}

		template<SystemConstraint T>
		void deleteSystem() {

			for(size_t i{0}; i < m_systems.size(); i++) {

				std::shared_ptr<AbstractSystem> castTest = std::static_pointer_cast<T>(m_systems[i]);

				if(castTest != nullptr) {  m_systems.erase(m_systems.begin() + i); }
			}
		}

		template<SystemConstraint T>
		std::shared_ptr<T> getSystem() {

			for(std::shared_ptr<AbstractSystem> currentSystem: m_systems) {

				std::shared_ptr<T> castTest = std::static_pointer_cast<T>(currentSystem);

				if(castTest != nullptr) { return castTest; }
			}

			return nullptr;
		}

		template<SystemConstraint T>
		bool systemIsCreated() {

			if(getSystem<T>() == nullptr) { return false; }
			return true;
		}

		template<SystemConstraint T>
		void addEntityToSystem(const Entity &entity) {

			std::shared_ptr<AbstractSystem> systemToAdd = getSystem<T>();

			if(systemToAdd == nullptr) { return; }

			if(systemToAdd->isInSystem(entity)) { return; } 

			systemToAdd->addEntity(entity, m_entitySignatureKeeper.getSignature(entity)); 
		}

		template<SystemConstraint T>
		void removeEntityOfSystem(const Entity &entity) {

			if(!entityIsInSystem<T>(entity)) { return; } 

			std::shared_ptr<AbstractSystem> systemToAdd = getSystem<T>();

			if(systemToAdd == nullptr) { return; }

			systemToAdd->removeEntity(entity); 
		}


		template<SystemConstraint T>
		bool entityIsInSystem(const Entity &entity) {

			std::shared_ptr<AbstractSystem> systemToSearch = getSystem<T>();

			if(systemToSearch == nullptr) { return false; }

			return systemToSearch->isInSystem(entity);
		}

		

	private:

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;    
		
		std::vector<std::shared_ptr<AbstractSystem>> m_systems;                 
};

}

#endif