#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include "GulgECS/Signature.hpp"
#include "GulgECS/AbstractSystem.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"

namespace Gg {

namespace System {

class GraphicSystem: public AbstractSystem {

	public:

		GraphicSystem();

		virtual void update(const double deltaTime);

	protected:

		std::vector<Entity> m_entities;
		const Signature m_systemSignature;
};

}

}

#endif