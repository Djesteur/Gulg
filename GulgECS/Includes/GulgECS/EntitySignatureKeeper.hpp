#ifndef ENTITY_SIGNATURE_KEEPER_HPP
#define ENTITY_SIGNATURE_KEEPER_HPP

#include <string>
#include <map>

#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {



/**
 * @brief      This class keep in memory the signatures of the entities
 */
class EntitySignatureKeeper {

	public:

		/**
		 * @brief      The default constructor
		 */
		EntitySignatureKeeper();

		/**
		 * @brief      Adds an new entity.
		 *
		 * @param[in]  entity  The entity
		 */
		void addEntity(const Entity entity);


		/**
		 * @brief      Remove an existing
		 *
		 * @param[in]  entity  The entity
		 */
		void removeEntity(const Entity entity);

		/**
		 * @brief      Check if the entity is already added
		 *
		 * @param[in]  entity  The entity
		 *
		 * @return     True if the entity is already added, else false
		 */
		bool entityExist(const Entity entity) const;

		/**
		 * @brief      Add a signature to the entity's signature.
		 *
		 * @param[in]  entity     The entity
		 * @param[in]  signature  The signature to add
		 */
		void addToSignature(const Entity entity, const Signature signature);

		/**
		 * @brief      Remove a signature from the entity's signature.
		 *
		 * @param[in]  entity     The entity
		 * @param[in]  signature  The signature to remove
		 */
		void removeFromSignature(const Entity entity, const Signature signature);

		/**
		 * @brief      Clone the entityToClone's signature into the clone's signature
		 *
		 * @param[in]  entityToClone  The entity to clone
		 * @param[in]  clone          The clone
		 */
		void cloneEntity(const Entity entityToClone, const Entity clone);
		
		/**
		 * @brief      Gets the signature of the entity
		 *
		 * @param[in]  entity  The entity
		 *
		 * @return     The signature.
		 */
		Signature getSignature(const Entity entity) const;

	private:

		std::map<Entity, Signature> m_signatures;                     
};

}

#endif