#ifndef ABSTRACT_SYSTEM_HPP
#define ABSTRACT_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "Signature.hpp"
#include "GulgDeclarations.hpp"

namespace Gg {

namespace System {

class AbstractSystem {

	public:

		AbstractSystem();

		virtual ~AbstractSystem(); 

		virtual void addEntity(const Entity newEntity, const Signature entitySignature);
		virtual void deleteEntity(const Entity newEntity);

		virtual void entitySignatureChanged(const Entity entity, const Signature newSignature);

		virtual void update(const double deltaTime) = 0;

		bool isInSystem(const Entity entity) const;

	protected:

		std::vector<Entity> m_entities;

		const Signature m_systemSignature;
};

}}

#endif