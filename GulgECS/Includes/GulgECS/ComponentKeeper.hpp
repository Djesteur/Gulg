#ifndef COMPONENT_KEEPER_HPP
#define COMPONENT_KEEPER_HPP

#include <string>
#include <map>
#include <memory>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/Signature.hpp"

using namespace Gg::Component;

namespace Gg {




/**
 * @brief      ComponentKeeper keep components in memory
 */
class ComponentKeeper {

	public:




		/**
		 * @brief      The default cnstructor
		 */
		ComponentKeeper();



		/**
		 * @brief      Add an entity.
		 *
		 * @param[in]  entity  The entity
		 */
		void addEntity(const Entity entity);
		


		/**
		 * @brief      Remove an entity and delete his components
		 *
		 * @param[in]  entity  The entity
		 */
		void removeEntity(const Entity entity);



		/**
		 * @brief      Creates a new component.
		 *
		 * @param[in]  entity  The entity which we add the component
		 * @param      args    The arguments for the constructor of the new component
		 *
		 * @tparam     T       The class of the component to add
		 *
		 * @return     A new component if entity hasn't already, else the existing component
		 */
		template<ComponentConstraint T, typename... Args>
		std::shared_ptr<AbstractComponent> createComponent(const Entity entity, Args&&... args) {

			if(!entityExist(entity)) { addEntity(entity); }

			if(!entityHasComponent<T>(entity)) {

				std::shared_ptr<T> newComponent = std::make_shared<T>(args...);
				m_components[entity].insert(std::make_pair(T::getType(), newComponent));
				return newComponent;
			}


			//If the component already exist, return it
			return getComponent<T>(entity);
		}



		/**
		 * @brief      Delete a component.
		 *
		 * @param[in]  entity  The entity which we will delete the component
		 *
		 * @tparam     T       The class of the component to delete
		 */
		template<ComponentConstraint T>
		void deleteComponent(const Entity entity) { deleteComponent(entity, T::getType()); }
		


		/**
		 * @brief      Delete a component.
		 *
		 * @param[in]  entity  The entity which we will delete the component
		 * @param[in]  type    The Component::Type of the component to delete
		 */
		void deleteComponent(const Entity entity, const Type type);




		/**
		 * @brief      Check if the entity is alreadyexisting for the ComponentKeeper
		 *
		 * @param[in]  entity  The entity
		 *
		 * @return     True if already added, else false
		 */
		bool entityExist(const Entity entity) const;



		/**
		 * @brief      Check if the entity has the asked component
		 *
		 * @param[in]  entity  The entity
		 *
		 * @tparam     T       The class of the component to check
		 *
		 * @return     True if the entity has the component, else false
		 */
		template<ComponentConstraint T>
		bool entityHasComponent(const Entity entity) { return entityHasComponent(entity, T::getType()); }



		/**
		 * @brief      Check if the entity has the asked component
		 *
		 * @param[in]  entity  The entity
		 * @param[in]  type    The type of the component to check
		 *
		 * @return     True if the entity has the component, else false
		 */
		bool entityHasComponent(const Entity entity, const Type type) const;





		/**
		 * @brief      Clone the components of entityToClone into clone
		 *
		 * @param[in]  entityToClone  The entity to clone
		 * @param[in]  clone          The clone
		 */
		void cloneEntity(const Entity entityToClone, const Entity clone);
		

		/**
		 * @brief      Get a component.
		 *
		 * @param[in]  entity  The entity
		 *
		 * @tparam     T       The class of the asked component
		 *
		 * @return     The component if the entity has one. Else, throw an exception (and return nullptr).
		 */
		template<ComponentConstraint T>
		std::shared_ptr<T> getComponent(const Entity entity) { return std::static_pointer_cast<T>(getComponent(entity, T::getType())); }




		/**
		 * @brief      Get a component.
		 *
		 * @param[in]  entity  The entity
		 * @param[in]  type    The type of the asked component
		 *
		 * @return     The component if the entity has one. Else, throw an exception (and return nullptr).
		 */
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity, const Type type) const;


	private:

		std::map<Entity, std::map<Type, std::shared_ptr<AbstractComponent>>> m_components;
                              
};

}

#endif