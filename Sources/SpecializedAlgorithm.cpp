#include "SpecializedAlgorithm.hpp"

namespace Gg {

SpecializedAlgorithm::SpecializedAlgorithm(const std::string componentToApply, ComponentKeeper &componentKeeper, SignatureLoader &signatureLoader): 
	Algorithm{componentKeeper, signatureLoader},
	m_componentToApply{componentToApply} {

	m_signature = signatureLoader.getSignature(m_componentToApply);
}

SpecializedAlgorithm::~SpecializedAlgorithm() {}

}