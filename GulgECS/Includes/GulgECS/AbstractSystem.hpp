#ifndef ABSTRACT_SYSTEM_HPP
#define ABSTRACT_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "GulgECS/ComponentKeeper.hpp"
#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

namespace System {




/**
 * @brief      Parent class for all systems used in Gulg
 * @details This is the parent class for all systems used in Gulg. The children must overload the update function, and have reference to a ComponentKeeper for the first argument of their constructor
 */

class AbstractSystem {

	public:



		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param      keeper           The ComponentKeeper used
		 * @param[in]  systemSignature  The system signature
		 */
		AbstractSystem(ComponentKeeper &keeper, const Signature systemSignature);


		/**
		 * @brief      Add an entity to the system.
		 *
		 * @param[in]  newEntity        The new entity
		 * @param[in]  entitySignature  The entity signature
		 */
		virtual void addEntity(const Entity newEntity, const Signature entitySignature);


		/**
		 * @brief      Remove an entity of the system
		 *
		 * @param[in]  entityToRemove  The new entity
		 */
		virtual void removeEntity(const Entity entityToRemove);


		/**
		 * @brief      Called by the GulgEngine when the signature of an entity changed. If the entity is in the system and his signature no long correspond at the signature of the system, it will be remove. 
		 *
		 * @param[in]  entity        The entity to check
		 * @param[in]  newSignature  The new signature of the entity
		 */
		virtual void entitySignatureChanged(const Entity entity, const Signature newSignature);


		/**
		 * @brief      Update the system.
		 *
		 * @param[in]  deltaTime  The elapsed time since the last call
		 */
		virtual void update(const double deltaTime) = 0;


		/**
		 * @brief      Determines whether the specified entity is in system.
		 *
		 * @param[in]  entity  The entity
		 *
		 * @return     True if the specified entity is in system, False otherwise.
		 */
		bool isInSystem(const Entity entity) const;

	protected:

		/// The list of entities to treat in the system
		std::vector<Entity> m_entities;


		/// The acces to the components of the entities
		ComponentKeeper &m_componentKeeper;

		///The signature of this system
		const Signature m_systemSignature;

};

}}

#endif