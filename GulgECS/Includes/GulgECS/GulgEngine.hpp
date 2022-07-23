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

/**
 * @brief      The GulgEngine class if the engine himself. His role is to centralize all services of other ECS classes
 */
class GulgEngine {

	public:

		/**
		 * @brief      The constructor
		 *
		 * @param[in]  wantLogs     If we want logs. Set by default at false
		 * @param[in]  logFilePath  If we want logs, the path to the file where logs will be write. By default: "LogFile.log"
		 */
		GulgEngine(const bool wantLogs = false, const std::string logFilePath = "LogFile.log");

		/**
		 * @brief      Create a new entity
		 *
		 * @return     The newly created entity
		 */
		Entity createEntity();
		
		/**
		 * @brief      Delete an existing entity
		 *
		 * @param[in]  entity   The entity to delete
		 */

		void deleteEntity(const Entity entity);


		/**
		 * @brief      Clone an entity: copy his signature, his componants and put it into the same systems
		 *
		 * @param[in]  entityToClone  The entity to clone
		 *
		 * @return     The cloned entity
		 */
		Entity cloneEntity(const Entity entityToClone);

		/**
		 * @brief      If the entity hasn't the asked component, create it. Else, return the already existing component.
		 *
		 * @param[in]  entity  The entity
		 * @param      args    The arguments for the constructor of the component
		 *
		 * @tparam     T       The class of the component to create
		 *
		 * @return     The asked component
		 */
		template<ComponentConstraint T, typename... Args>
		std::shared_ptr<T> createComponent(const Entity entity, Args&&... args) {

			if(!m_componentKeeper.entityHasComponent<T>(entity)) {

				std::shared_ptr<T> newComponent = std::static_pointer_cast<T>(m_componentKeeper.createComponent<T>(entity, args...));
				m_entitySignatureKeeper.addToSignature(entity, ComponentSignatureKeeper::getSignature(T::getType()));

				return newComponent;
			}

			//If the entity already have the component, return it.
			return std::static_pointer_cast<T>(m_componentKeeper.getComponent(entity, T::getType()));
		}


		/**
		 * @brief      Delete a component
		 *
		 * @param[in]  entity  The entity that own the component
		 *
		 * @tparam     T       The class of the component to delete
		 */
		template<ComponentConstraint T>
		void deleteComponent(const Entity entity) { deleteComponent(entity, T::getType()); }

		/**
		 * @brief      Delete a component
		 *
		 * @param[in]  entity  The entity that own the component
		 * @param[in]  type    The type of the component to delete
		 */
		void deleteComponent(const Entity entity, const Type type);

		/**
		 * @brief      Check if the entity have the asked component
		 *
		 * @param[in]  entity  The entity
		 *
		 * @tparam     T       The class of the asked component
		 *
		 * @return     True if the entity have the component, else false
		 */
		template<ComponentConstraint T>
		bool entityHasComponent(const Entity entity) { return entityHasComponent(entity, T::getType()); }



		/**
		 * @brief      Check if the entity have the asked component
		 *
		 * @param[in]  entity  The entity
		 *
		 * @param[in]  type    The type of the asked component
		 *
		 * @return     True if the entity have the component, else false
		 */
		bool entityHasComponent(const Entity entity, const Type type);



		/**
		 * @brief      Get the asked component.
		 *
		 * @param[in]  entity  The entity that own the component
		 *
		 * @tparam     T       The class of the asked component
		 *
		 * @return     The component
		 */
		template<ComponentConstraint T>
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity) { return getComponent(entity, T::getType()); }



		/**
		 * @brief      Get the asked component.
		 *
		 * @param[in]  entity  The entity that own the component
		 *
		 * @param[in]  type    The type of the asked component
		 *
		 * @return     The component
		 */
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity, const Type type);




		/**
		 * @brief      Creates a new system. If the system already exist, return it
		 *
		 * @param      args  The argument for the system's constructor
		 *
		 * @tparam     T     The class of the system
		 *
		 * @return     The asked system
		 */
		template<SystemConstraint T, typename... Args>
		std::shared_ptr<T> createSystem(Args&&... args) {

			if(systemIsCreated<T>()) { return getSystem<T>(); }

			m_systems.emplace_back(std::make_shared<T>(m_componentKeeper, args...));
			return std::static_pointer_cast<T>(m_systems.back());
		}

		/**
		 * @brief      Delete an ecisting system
		 *
		 * @tparam     T     The class of the system
		 */
		template<SystemConstraint T>
		void deleteSystem() {

			for(size_t i{0}; i < m_systems.size(); i++) {

				std::shared_ptr<AbstractSystem> castTest = std::static_pointer_cast<T>(m_systems[i]);

				if(castTest != nullptr) {  m_systems.erase(m_systems.begin() + i); }
			}
		}

		/**
		 * @brief      Get an existing system
		 *
		 * @tparam     T     The class of the asked system
		 *
		 * @return     The system if he exist, else nullptr
		 */
		template<SystemConstraint T>
		std::shared_ptr<T> getSystem() {

			for(std::shared_ptr<AbstractSystem> currentSystem: m_systems) {

				std::shared_ptr<T> castTest = std::static_pointer_cast<T>(currentSystem);

				if(castTest != nullptr) { return castTest; }
			}

			return nullptr;
		}



		/**
		 * @brief      Check if the asked system exist
		 *
		 * @tparam     T     The class of the system
		 *
		 * @return     True if the system exist, else false
		 */
		template<SystemConstraint T>
		bool systemIsCreated() {

			if(getSystem<T>() == nullptr) { return false; }
			return true;
		}



		/**
		 * @brief      Add an entity to the system if their signatures correspond
		 *
		 * @param[in]  entity  The entity to add
		 *
		 * @tparam     T       The class of the system
		 */
		template<SystemConstraint T>
		void addEntityToSystem(const Entity &entity) {

			std::shared_ptr<AbstractSystem> systemToAdd = getSystem<T>();

			if(systemToAdd == nullptr) { return; }

			if(systemToAdd->isInSystem(entity)) { return; } 

			systemToAdd->addEntity(entity, m_entitySignatureKeeper.getSignature(entity)); 
		}

		/**
		 * @brief      Removes an entity of system.
		 *
		 * @param[in]  entity  The entity
		 *
		 * @tparam     T       The class of the system
		 */
		template<SystemConstraint T>
		void removeEntityOfSystem(const Entity &entity) {

			if(!entityIsInSystem<T>(entity)) { return; } 

			std::shared_ptr<AbstractSystem> systemToAdd = getSystem<T>();

			if(systemToAdd == nullptr) { return; }

			systemToAdd->removeEntity(entity); 
		}


		/**
		 * @brief      Check if an entity is in a system
		 *
		 * @param[in]  entity  The entity
		 *
		 * @tparam     T       The class of the system to check
		 *
		 * @return     True is the entity is in the system, else false
		 */
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