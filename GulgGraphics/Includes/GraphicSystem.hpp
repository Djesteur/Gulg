#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include "GulgECS/Signature.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

namespace System {

class GraphicSystem: AbstractSystem {

	public:

		GraphicSystem();

		virtual void update(const double deltaTime);

	protected:

		std::vector<Entity> m_entities;

		const Signature m_systemSignature;
};

}}

#endif