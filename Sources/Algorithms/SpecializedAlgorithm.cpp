#include "Algorithms/SpecializedAlgorithm.hpp"

namespace Gg {

namespace Algorithm {

SpecializedAlgorithm::SpecializedAlgorithm(const std::string componentToApply, GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	m_componentToApply{componentToApply} {

	m_signature = m_gulgEngine.getComponentSignature(m_componentToApply);
}

SpecializedAlgorithm::SpecializedAlgorithm(const std::vector<std::string> componentsToApply, GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	m_componentsToApply{componentsToApply} {

	m_signature = m_gulgEngine.getComponentSignature(componentsToApply[0]);

	for(const std::string &currentComponent: componentsToApply) {

		m_signature += m_gulgEngine.getComponentSignature(currentComponent);
	}
}

SpecializedAlgorithm::~SpecializedAlgorithm() {}

}}