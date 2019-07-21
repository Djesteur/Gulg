#ifndef SPECIALIZED_ALGORITHM_HPP
#define SPECIALIZED_ALGORITHM_HPP

#include <string>

#include "Algorithms/Algorithm.hpp"

namespace Gg {

class SpecializedAlgorithm: public AbstractAlgorithm {

	public:

		SpecializedAlgorithm(const std::string componentToApply, GulgEngine &gulgEngine);
		SpecializedAlgorithm(const std::vector<std::string> componentToApply, GulgEngine &gulgEngine);
		virtual ~SpecializedAlgorithm(); 

	protected:

		const std::string m_componentToApply;
		const std::vector<std::string> m_componentsToApply;
};

}

#endif