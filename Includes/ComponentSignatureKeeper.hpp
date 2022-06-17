#ifndef COMPONENT_SIGNATURE_KEEPER_HPP
#define COMPONENT_SIGNATURE_KEEPER_HPP

#include <map>
#include <memory>

#include "Signature.hpp"
#include "GulgDeclarations.hpp"

namespace Gg {

class ComponentSignatureKeeper {

	public:

		ComponentSignatureKeeper();

		void registerComponentType(const Component::Type &newType);
		void unregisterComponentType(const Component::Type &typeToUnregister);

		bool componentTypeHasSignature(const Component::Type &typeToTest) const;

		Signature getSignature(const Component::Type &componentTypeToGet) const;
		Component::Type getComponentType(const Signature  &signatureToGet) const;

	private:

		std::map<Component::Type, Signature> m_signatures;                     
};

}

#endif