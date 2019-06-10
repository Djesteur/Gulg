#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <algorithm>

#include "ComponentKeeper.hpp"
#include "Signature.hpp"
#include "SignatureLoader.hpp"
#include "GulgDeclarations.hpp"

namespace Gg {

class Algorithm {

	public:

		Algorithm(ComponentKeeper &keeper, SignatureLoader &signatureLoader);
		virtual ~Algorithm(); 

		void addEntity(const Entity newEntity);
		void deleteEntity(const Entity entity);

		Signature getSignature() const;

		virtual void apply() = 0; 

	protected:

		ComponentKeeper &m_componentKeeper;
		std::vector<Entity> m_entitiesToApply;

		Signature m_signature;
};

}

#endif