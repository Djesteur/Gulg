#include "Algorithms/SpecializedAlgorithm.hpp"

namespace Gg {

namespace Algorithm {

SpecializedAlgorithm::SpecializedAlgorithm(const ComponentType type, GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	m_componentToApply{type} {

	m_signature = Signature{m_componentToApply};
}

SpecializedAlgorithm::~SpecializedAlgorithm() {}

}}