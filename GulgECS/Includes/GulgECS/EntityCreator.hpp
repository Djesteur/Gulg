#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include <stdexcept>
#include <deque>
#include <string>

#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {



/**
 * @brief      This class create new entities, and ensure they are uniques
 */

class EntityCreator {

	public:


		/**
		 * @brief      Default constructor
		 */
		EntityCreator();


		/**
		 * @brief      Creates an new entity.
		 *
		 * @return     The new entity.
		 */
		Entity createEntity();
		

		/**
		 * @brief      Removes an existing entity.
		 *
		 * @param[in]  removeEntity  The entity to remove
		 */
		void deleteEntity(const Entity removeEntity);

	private:



		/**
		 * @brief      If they are not enought entities remaining, add places in the reserve
		 *
		 * @param[in]  numberOfEntititesToReserve  The number of entitites to reserve
		 */
		void addToReserve(const uint32_t numberOfEntititesToReserve);
                              
		std::deque<Entity> m_nextEntities;
		uint32_t m_lastReservedEntity;

};

}

#endif