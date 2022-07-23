#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <vector>
#include <array>
#include <string>
#include <sstream>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"


namespace Gg {



/**
 * @brief      A signature for an entity, component or a system
 */
class Signature {

	public:

		/**
		 * @brief      Default constructor
		 */
		Signature();


		/**
		 * @brief      Copy constructor
		 *
		 * @param[in]  second  The signature to copy
		 */
		Signature(const Signature &second);


		/**
		 * @brief      Create the signature as a sum of signature
		 *
		 * @param[in]  signaturesToAdd  The signatures to add
		 */
		Signature(const std::vector<Signature> &signaturesToAdd);
		
		/**
		 * @brief      Create from and array of bits (for internal uses only)
		 *
		 * @param[in]  signatureArray  The signature array
		 */
		Signature(const std::array<bool, Component::MaxComponentType> &signatureArray);

		/**
		 * @brief      The copy operator
		 *
		 * @param[in]  second  The signature to copy
		 */
		void operator=(const Signature &second);

		/**
		 * @brief      Equality operator.
		 *
		 * @param[in]  second  The signature to compare
		 *
		 * @return     The result of the equality
		 */
		bool operator==(const Signature &second) const;

		/**
		 * @brief      Addition operator.
		 *
		 * @param[in]  second  The signature to add
		 *
		 * @return     The result of the addition
		 */
		Signature operator+(const Signature &second) const;	

		/**
		 * @brief      Addition assignment operator.
		 *
		 * @param[in]  second  The signature to add
		 */
		void operator+=(const Signature &second);

		/**
		 * @brief      Subtraction operator.
		 *
		 * @param[in]  second  The signature to remove
		 *
		 * @return     The result of the subtraction
		 */
		Signature operator-(const Signature &second) const;
		
		/**
		 * @brief      Subtraction assignment operator.
		 *
		 * @param[in]  second  The signature
		 */
		void operator-=(const Signature &second);

		/**
		 * @brief      Bitwise 'or' operator.
		 *
		 * @param[in]  second  The second signature
		 *
		 * @return     The result of the bitwise 'or'
		 */
		Signature operator|(const Signature &second) const;
		
		/**
		 * @brief      Bitwise 'or' assignment operator.
		 *
		 * @param[in]  second  The second signature
		 */
		void operator|=(const Signature &second);

		/**
		 * @brief      Bitwise 'and' operator.
		 *
		 * @param[in]  second  The second signature
		 *
		 * @return     The result of the bitwise 'and'
		 */
		Signature operator&(const Signature &second) const;
		
		/**
		 * @brief      Bitwise 'and' assignment operator.
		 *
		 * @param[in]  second  The second signature
		 */
		void operator&=(const Signature &second);

		/**
		 * @brief      Check if the second signature is contained inside this signature
		 *
		 * @param[in]  second  The second signature
		 *
		 * @return     True if the second signature is contained inside this signature, else false
		 */
		bool containSignature(const Signature &second) const;

		/**
		 * @brief      Return the signature as String
		 *
		 * @return     The signature as String
		 */
		std::string asString() const;

	private:

		std::array<bool, Component::MaxComponentType> m_signature;                  
};

/**
 * @brief      Add the signaute as string into the stream
 *
 * @param      stream  The stream
 * @param[in]  signature    The signature
 *
 * @return     The input stream
 */
std::ostream& operator<<(std::ostream &stream, const Signature &signature);

}

#endif