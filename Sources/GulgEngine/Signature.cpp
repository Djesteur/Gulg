#include "GulgEngine/Signature.hpp"

namespace Gg {

Signature::Signature() {}

Signature::Signature(ComponentType type) { m_signature[static_cast<size_t>(type)] = true; }

Signature::Signature(std::vector<ComponentType> types) {

	for(size_t i{0}; i < NbComponentType; i++) { m_signature[static_cast<size_t>(types[i])] = true; }
}

Signature::Signature(const std::array<bool, NbComponentType> &signature): m_signature{signature} {}

Signature::Signature(const Signature &second): m_signature{second.m_signature} {}

void Signature::operator=(const Signature &second) { m_signature = second.m_signature; }

bool Signature::operator<(const Signature &second) const {

	for(size_t i{0}; i < NbComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i] && m_signature[i] == true) { return false; } // So second.m_signature[i] == false
	}

	return true;
}

bool Signature::operator>(const Signature &second) const {

	for(size_t i{0}; i < NbComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i] && m_signature[i] == false) { return false; } // So second.m_signature[i] == false
	}

	return true;
}

bool Signature::operator==(const Signature &second) const {

	for(size_t i{0}; i < NbComponentType; i++) { 

		if(m_signature[i] != second.m_signature[i]) { return false; } 
	}

	return true;
}

Signature Signature::operator+(const Signature &second) const {

	std::array<bool, NbComponentType> newSignature{m_signature};

	for(size_t i{0}; i < NbComponentType; i++) { newSignature[i] = m_signature[i] | second.m_signature[i]; }
	return Signature{newSignature};
}

void Signature::operator+=(const Signature &second) {

	for(size_t i{0}; i < NbComponentType; i++) { m_signature[i] = m_signature[i] | second.m_signature[i]; }
}

Signature Signature::operator-(const Signature &second) const {

	std::array<bool, NbComponentType> newSignature{m_signature};

	for(size_t i{0}; i < NbComponentType; i++) { 

		if(m_signature[i] == true && m_signature[i] == second.m_signature[i]) { newSignature[i] = false; }
		else { newSignature[i] = m_signature[i] | second.m_signature[i]; }
	}

	return Signature{newSignature};
}

void Signature::operator-=(const Signature &second) {

	for(size_t i{0}; i < NbComponentType; i++) { 

		if(m_signature[i] == true && second.m_signature[i] == true) { m_signature[i] = false; }
	}
}

Signature Signature::operator|(const Signature &second) const {

	std::array<bool, NbComponentType> newSignature{m_signature};

	for(size_t i{0}; i < NbComponentType; i++) { newSignature[i] = m_signature[i] | second.m_signature[i]; }

	return Signature{newSignature};
}

void Signature::operator|=(const Signature &second) {

	for(size_t i{0}; i < NbComponentType; i++) { m_signature[i] = m_signature[i] | second.m_signature[i]; }
}


Signature Signature::operator&(const Signature &second) const {

	std::array<bool, NbComponentType> newSignature{m_signature};

	for(size_t i{0}; i < NbComponentType; i++) { newSignature[i] = m_signature[i] & second.m_signature[i]; }

	return Signature{newSignature};
}

void Signature::operator&=(const Signature &second) {

	for(size_t i{0}; i < NbComponentType; i++) { m_signature[i] = m_signature[i] & second.m_signature[i]; }
}

std::string Signature::asString() const {

	std::string result;
	for(size_t i{0}; i < NbComponentType; i++) { result += std::to_string(m_signature[i]); }
	return result;
}

std::ostream& operator<<(std::ostream &stream, const Signature &sign) {

	stream << sign.asString();
	return stream;
}

}