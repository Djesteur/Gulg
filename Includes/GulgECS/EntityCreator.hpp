#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include <stdexcept>
#include <deque>
#include <string>

#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {


class EntityCreator {

	public:

		EntityCreator();

		Entity createEntity();
		void freeEntity(const Entity freeEntity);

	private:

		void addToReserve(const uint32_t numberOfEntititesToReserve);
                              
		std::deque<Entity> m_nextEntities;
		uint32_t m_lastReservedEntity;

};

}

#endif