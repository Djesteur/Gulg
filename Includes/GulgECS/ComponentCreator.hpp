#ifndef COMPONENT_CREATOR_KEEPER_HPP
#define COMPONENT_CREATOR_KEEPER_HPP

#include <memory>


#include "GulgECS/Signature.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/ComponentKeeper.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"

namespace Gg {

class ComponentCreator {

	public:

		ComponentCreator(ComponentSignatureKeeper &componentSignatureKeeper);

		void registerComponent(const std::shared_ptr<Component::AbstractComponent> componentToRegister);
		void unregisterComponent(const std::shared_ptr<Component::AbstractComponent> componentToUnregister);

		bool componentIsRegistered(const std::shared_ptr<Component::AbstractComponent> componentToTest) const;
		bool componentIsRegistered(const Component::Type &typeToTest) const;

		Signature getComponentSignature(const std::shared_ptr<Component::AbstractComponent> signatureToGet) const;
		Signature getComponentSignature(const Component::Type &signatureToGet) const;

		std::shared_ptr<Component::AbstractComponent> createComponent(const Component::Type type) const;


	private:

		std::map<Signature, std::shared_ptr<Component::AbstractComponent>> m_componentSignatures;
		ComponentSignatureKeeper &m_componentSignatureKeeper;                  
};

}

#endif