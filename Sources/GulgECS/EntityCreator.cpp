#include "GulgECS/EntityCreator.hpp"

namespace Gg {

	
EntityCreator::EntityCreator(): m_lastReservedEntity{0} {}


Entity EntityCreator::createEntity() {

	if(m_nextEntities.size() == 0) { addToReserve(1); }

	Entity newEntity{m_nextEntities.front()};
	m_nextEntities.pop_front();
	return newEntity;
}

void EntityCreator::freeEntity(const Entity freeEntity) { m_nextEntities.emplace_back(freeEntity); }

void EntityCreator::addToReserve(const uint32_t numberOfEntititesToReserve) {

	for(uint32_t i{0}; i < numberOfEntititesToReserve; i++) {

		m_lastReservedEntity++;
		m_nextEntities.emplace_back(m_lastReservedEntity);
	}
}

}