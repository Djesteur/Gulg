#ifndef ABSTRACT_SYSTEM_HPP
#define ABSTRACT_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "GulgECS/ComponentKeeper.hpp"
#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

class GulgEngine;

namespace System {

class AbstractSystem {

	public:

		AbstractSystem(ComponentKeeper &keeper, const Signature systemSignature);

		virtual ~AbstractSystem(); 

		virtual void addEntity(const Entity newEntity, const Signature entitySignature);
		virtual void removeEntity(const Entity newEntity);

		virtual void entitySignatureChanged(const Entity entity, const Signature newSignature);

		virtual void update(const double deltaTime) = 0;

		bool isInSystem(const Entity entity) const;

	protected:

		std::vector<Entity> m_entities;

		ComponentKeeper &m_componentKeeper;
		const Signature m_systemSignature;

};

}}

#endif