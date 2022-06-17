#include "ComponentCreator.hpp"

namespace Gg {

ComponentCreator::ComponentCreator(ComponentSignatureKeeper &componentSignatureKeeper): m_componentSignatureKeeper{componentSignatureKeeper} {}


void ComponentCreator::registerComponent(const std::shared_ptr<Component::AbstractComponent> componentToRegister) {

	if(!m_componentSignatureKeeper.componentTypeHasSignature(componentToRegister->getType())) { m_componentSignatureKeeper.registerComponentType(componentToRegister->getType()); }

	if(m_componentSignatures.find(m_componentSignatureKeeper.getSignature(componentToRegister->getType())) == m_componentSignatures.end()) {

		m_componentSignatures.insert(std::make_pair(m_componentSignatureKeeper.getSignature(componentToRegister->getType()), componentToRegister));
	}
}

void ComponentCreator::unregisterComponent(const std::shared_ptr<Component::AbstractComponent> componentToUnregister) {

	if(m_componentSignatureKeeper.componentTypeHasSignature(componentToUnregister->getType())
	&& m_componentSignatures.find(m_componentSignatureKeeper.getSignature(componentToUnregister->getType())) != m_componentSignatures.end()) {

		m_componentSignatures.erase(m_componentSignatureKeeper.getSignature(componentToUnregister->getType()));
	}
}


bool ComponentCreator::componentIsRegistered(const std::shared_ptr<Component::AbstractComponent> componentToTest) const {

	return componentIsRegistered(componentToTest->getType());
}

bool ComponentCreator::componentIsRegistered(const Component::Type &typeToTest) const { 

	return m_componentSignatureKeeper.componentTypeHasSignature(typeToTest) 
	&& m_componentSignatures.find(m_componentSignatureKeeper.getSignature(typeToTest)) != m_componentSignatures.end();
}


Signature ComponentCreator::getComponentSignature(const std::shared_ptr<Component::AbstractComponent> signatureToGet) const {

	return getComponentSignature(signatureToGet->getType());

}

Signature ComponentCreator::getComponentSignature(const Component::Type &signatureToGet) const {

	if(componentIsRegistered(signatureToGet)) { return m_componentSignatureKeeper.getSignature(signatureToGet); }

	return Signature{};
}


std::shared_ptr<Component::AbstractComponent> ComponentCreator::createComponent(const Component::Type type) const {

	if(componentIsRegistered(type)) { return m_componentSignatures.at(m_componentSignatureKeeper.getSignature(type))->clone(); }

	return nullptr;
}


}
