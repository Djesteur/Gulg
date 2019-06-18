#ifndef SPECIALIZED_ALGORITHM_HPP
#define SPECIALIZED_ALGORITHM_HPP

#include "Algorithm.hpp"

namespace Gg {

class SpecializedAlgorithm: public Algorithm {

	public:

		SpecializedAlgorithm(const std::string componentToApply, ComponentKeeper &componentKeeper, SignatureLoader &signatureLoader);
		virtual ~SpecializedAlgorithm(); 

	protected:

		const std::string m_componentToApply;
};

}

#endif