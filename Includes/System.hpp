#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <memory>

#include "ComponentKeeper.hpp"
#include "Signature.hpp"
#include "SignatureLoader.hpp"
#include "EntitySignatureKeeper.hpp"
#include "Algorithm.hpp"
#include "Graphics/SpriteAlgorithm.hpp"
#include "GulgDeclarations.hpp"

namespace Gg {

class System {

	public:

		System(EntitySignatureKeeper &entitySignatureKeeper, SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper);
		virtual ~System(); 

		void addEntity(const Entity newEntity);
		void deleteEntity(const Entity newEntity);

		virtual void applyAlgorithms();

	protected:

		std::vector<std::unique_ptr<Algorithm>> m_algorithms;
		EntitySignatureKeeper &m_entitySignatureKeeper;      
};

}

#endif