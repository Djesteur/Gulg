#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "GulgEngine/GulgEngine.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

namespace Gg {

namespace Systems {

class AbstractSystem {

	public:

		AbstractSystem(GulgEngine &gulgEngine, const Signature signature);

		virtual ~AbstractSystem(); 

		virtual void addEntity(const Entity newEntity);
		virtual void deleteEntity(const Entity newEntity);

		virtual void apply() = 0;

	protected:

		GulgEngine &m_gulgEngine;
		std::vector<Entity> m_entities;
		const Signature m_systemSignature;
};

}}

#endif