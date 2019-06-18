#include "Algorithms/SpecializedAlgorithm.hpp"

namespace Gg {

SpecializedAlgorithm::SpecializedAlgorithm(const std::string componentToApply, GulgEngine &gulgEngine): 
	Algorithm{gulgEngine},
	m_componentToApply{componentToApply} {

	m_signature = m_gulgEngine.getComponentSignature(m_componentToApply);
}

SpecializedAlgorithm::~SpecializedAlgorithm() {}

}