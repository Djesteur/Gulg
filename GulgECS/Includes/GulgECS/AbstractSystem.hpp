#ifndef ABSTRACT_SYSTEM_HPP
#define ABSTRACT_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

class GulgEngine;

namespace System {

class AbstractSystem {

	public:

		AbstractSystem(GulgEngine &engine, const Signature systemSignature);

		virtual ~AbstractSystem(); 

		virtual void addEntity(const Entity newEntity, const Signature entitySignature);
		virtual void deleteEntity(const Entity newEntity);

		virtual void entitySignatureChanged(const Entity entity, const Signature newSignature);

		virtual void update(const double deltaTime) = 0;

		bool isInSystem(const Entity entity) const;

	protected:

		std::vector<Entity> m_entities;

		GulgEngine &m_gulgEngine;
		const Signature m_systemSignature;
};

}}

#endif