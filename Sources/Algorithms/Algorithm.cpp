#include "Algorithms/Algorithm.hpp"

namespace Gg {

Algorithm::Algorithm(GulgEngine &gulgEngine): m_gulgEngine{gulgEngine} {}

Algorithm::~Algorithm() {}

void Algorithm::addEntity(const Entity newEntity) { 

	std::vector<Entity>::iterator it{std::find(m_entitiesToApply.begin(), m_entitiesToApply.end(), newEntity)};
	if(it == m_entitiesToApply.end()) { m_entitiesToApply.emplace_back(newEntity); }
}

void Algorithm::deleteEntity(const Entity entity) {

	std::vector<Entity>::iterator it{std::find(m_entitiesToApply.begin(), m_entitiesToApply.end(), entity)};
	if(it != m_entitiesToApply.end()) { m_entitiesToApply.erase(it); }
}

Signature Algorithm::getSignature() const { return m_signature; }

}