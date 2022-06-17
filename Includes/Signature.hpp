#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <vector>
#include <array>

#include "GulgDeclarations.hpp"

namespace Gg {



class Signature {

	public:

		Signature();
		Signature(const Signature &second);
		Signature(const std::vector<Signature> &signaturesToAdd);
		Signature(const std::array<bool, MaxComponentType> &signatureArray);

		void operator=(const Signature &second);

		bool operator<(const Signature &second) const;
		bool operator>(const Signature &second) const;
		bool operator==(const Signature &second) const;

		Signature operator+(const Signature &second) const;	
		void operator+=(const Signature &second);

		Signature operator-(const Signature &second) const;
		void operator-=(const Signature &second);

		Signature operator|(const Signature &second) const;
		void operator|=(const Signature &second);

		Signature operator&(const Signature &second) const;
		void operator&=(const Signature &second);

		bool containSignature(const Signature &second) const;

		std::string asString() const;

		size_t getSignatureSize() const;

	private:

		std::array<bool, MaxComponentType> m_signature;                  
};

std::ostream& operator<<(std::ostream &stream, const Signature &sign);

}

#endif