#include "GulgECS/Signature.hpp"

namespace Gg {

Signature::Signature() { 

	for(size_t i{0}; i < Component::MaxComponentType; i++) { m_signature[i] = false; } 
}

Signature::Signature(const Signature &second): m_signature{second.m_signature} {}

Signature::Signature(const std::vector<Signature> &signaturesToAdd) {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { m_signature[i] = false; } 

	for(Signature currentSignature: signaturesToAdd) { this->operator+=(currentSignature); }
}
		
Signature::Signature(const std::array<bool, Component::MaxComponentType> &signatureArray): m_signature{signatureArray} {}

void Signature::operator=(const Signature &second) { m_signature = second.m_signature; }

bool Signature::operator<(const Signature &second) const {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i] && m_signature[i] == true) { return false; } // So second.m_signature[i] == false
	}

	return true;
}

bool Signature::operator>(const Signature &second) const {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i] && m_signature[i] == false) { return false; } // So second.m_signature[i] == false
	}

	return true;
}

bool Signature::operator==(const Signature &second) const {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i]) { return false; } 
	}

	return true;
}

Signature Signature::operator+(const Signature &second) const {

	std::array<bool, Component::MaxComponentType> newSignature{m_signature};

	for(size_t i{0}; i < Component::MaxComponentType; i++) { newSignature[i] = m_signature[i] | second.m_signature[i]; }
	return Signature{newSignature};
}

void Signature::operator+=(const Signature &second) {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { m_signature[i] = m_signature[i] | second.m_signature[i]; }
}

Signature Signature::operator-(const Signature &second) const {

	std::array<bool, Component::MaxComponentType> newSignature{m_signature};

	for(size_t i{0}; i < Component::MaxComponentType; i++) { 

		if(m_signature[i] == true && m_signature[i] == second.m_signature[i]) { newSignature[i] = false; }
		else { newSignature[i] = m_signature[i] | second.m_signature[i]; }
	}

	return Signature{newSignature};
}

void Signature::operator-=(const Signature &second) {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { 

		if(m_signature[i] == true && second.m_signature[i] == true) { m_signature[i] = false; }
	}
}

Signature Signature::operator|(const Signature &second) const {

	std::array<bool, Component::MaxComponentType> newSignature{m_signature};

	for(size_t i{0}; i < Component::MaxComponentType; i++) { newSignature[i] = m_signature[i] | second.m_signature[i]; }

	return Signature{newSignature};
}

void Signature::operator|=(const Signature &second) {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { m_signature[i] = m_signature[i] | second.m_signature[i]; }
}


Signature Signature::operator&(const Signature &second) const {

	std::array<bool, Component::MaxComponentType> newSignature{m_signature};

	for(size_t i{0}; i < Component::MaxComponentType; i++) { newSignature[i] = m_signature[i] & second.m_signature[i]; }

	return Signature{newSignature};
}

void Signature::operator&=(const Signature &second) {

	for(size_t i{0}; i < Component::MaxComponentType; i++) { m_signature[i] = m_signature[i] & second.m_signature[i]; }
}

bool Signature::containSignature(const Signature &second) const {

	if(this->operator&(second) == second) { return true; }

	return false;
}

std::string Signature::asString() const {

	std::string result;
	for(size_t i{0}; i < Component::MaxComponentType; i++) { result += std::to_string(m_signature[i]); }
	return result;
}

std::ostream& operator<<(std::ostream &stream, const Signature &sign) {

	stream << sign.asString();
	return stream;
}

}