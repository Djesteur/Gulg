#include "GraphicSystem.hpp"

GraphicSystem::GraphicSystem(): m_systemSignature{} {}


void GraphicSystem::update(const double deltaTime) {

}


	protected:

		std::vector<Entity> m_entities;

		const Signature m_systemSignature;