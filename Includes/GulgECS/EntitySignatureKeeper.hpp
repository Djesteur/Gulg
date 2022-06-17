#ifndef ENTITY_SIGNATURE_KEEPER_HPP
#define ENTITY_SIGNATURE_KEEPER_HPP

#include <string>
#include <map>

#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

class EntitySignatureKeeper {

	public:

		EntitySignatureKeeper();

		void addEntity(const Entity entity);
		void deleteEntity(const Entity entity);

		bool entityExist(const Entity entity) const;

		void addToSignature(const Entity entity, const Signature signature);
		void deleteToSignature(const Entity entity, const Signature signature);

		void cloneEntity(const Entity entityToClone, const Entity clone);
		
		Signature getSignature(const Entity entity) const;

	private:

		std::map<Entity, Signature> m_signatures;                     
};

}

#endif