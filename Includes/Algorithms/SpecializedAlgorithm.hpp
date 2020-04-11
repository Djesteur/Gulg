#ifndef SPECIALIZED_ALGORITHM_HPP
#define SPECIALIZED_ALGORITHM_HPP

#include <string>

#include "Algorithms/Algorithm.hpp"

namespace Gg {

namespace Algorithm {

class SpecializedAlgorithm: public AbstractAlgorithm {

	public:

		SpecializedAlgorithm(const ComponentType type, GulgEngine &gulgEngine);
		virtual ~SpecializedAlgorithm(); 

	protected:

		const ComponentType m_componentToApply;
};

}}

#endif