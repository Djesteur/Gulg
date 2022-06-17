#include "GulgECS/ComponentSignatureKeeper.hpp"

namespace Gg {


ComponentSignatureKeeper::ComponentSignatureKeeper() {}

void ComponentSignatureKeeper::registerComponentType(const Component::Type &newType) {

	if(!componentTypeHasSignature(newType)) {

		for(size_t onePosition{0}; onePosition < MaxComponentType; onePosition++) {

			std::array<bool, MaxComponentType> newSignatureToTest;

			for(size_t i{0}; i < MaxComponentType; i++) {

				if(i == onePosition) { newSignatureToTest[i] = true; }
				else { newSignatureToTest[i] = false; }
			}

			Signature newSignature{newSignatureToTest};

			bool alreadyExist{false};

			for (std::map<Component::Type, Signature>::iterator it{m_signatures.begin()}; it != m_signatures.end(); it++) {

				if(newSignature == it->second) { alreadyExist = true; }
			}

			if(!alreadyExist) {

				m_signatures.insert(std::make_pair(newType, newSignature));
				return;
			}
		}
	}
}

void ComponentSignatureKeeper::unregisterComponentType(const Component::Type &typeToUnregister) {

	if(componentTypeHasSignature(typeToUnregister)) { m_signatures.erase(m_signatures.find(typeToUnregister)); }
}


bool ComponentSignatureKeeper::componentTypeHasSignature(const Component::Type &typeToTest) const {

	if(m_signatures.find(typeToTest) != m_signatures.end()) { return true; }

	return false;
}


Signature ComponentSignatureKeeper::getSignature(const Component::Type &componentTypeToGet) const {

	if(componentTypeHasSignature(componentTypeToGet)) { return m_signatures.at(componentTypeToGet); }

	return Signature{};
}

Component::Type ComponentSignatureKeeper::getComponentType(const Signature  &signatureToGet) const {

	for (std::map<Component::Type, Signature>::const_iterator it = m_signatures.begin(); it != m_signatures.end(); it++) {

		if(signatureToGet == it->second) { return it->first; }
	}

	return Component::Type::Default;
}

}