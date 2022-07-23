#ifndef COMPONENT_SIGNATURE_KEEPER_HPP
#define COMPONENT_SIGNATURE_KEEPER_HPP

#include <map>
#include <memory>

#include "GulgECS/Signature.hpp"
#include "GulgECS/ComponentTypes.hpp"
#include "GulgECS/GulgDeclarations.hpp"

namespace Gg {

class ComponentSignatureKeeper {

	public:

		template<Component::ComponentConstraint T>
		static Signature getSignature(const Component::Type &componentTypeToGet) { return getSignature(T::getType()); }

		static Signature getSignature(const Component::Type &componentTypeToGet);
		static void Init();

	private:

		ComponentSignatureKeeper();

		//Dont touch this, need for the auto-generated program
		static std::map<Component::Type, Signature> m_signatures;                     
};

}

#endif