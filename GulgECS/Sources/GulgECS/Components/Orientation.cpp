#include "GulgECS/Components/Orientation.hpp"

namespace Gg {

namespace Component {

Orientation::Orientation(): m_orientation{0.f} {}

Orientation::Orientation(const float orientation, const bool unitIsRadians): m_orientation{orientation} { 

	if(!unitIsRadians) { m_orientation = glm::radians(orientation); }
	normalizeOrientation(); 
}


std::shared_ptr<AbstractComponent> Orientation::clone() const { return std::make_shared<Orientation>(m_orientation); }

float Orientation::getOrientation(const bool unitIsRadians) const { 

	if(unitIsRadians) { return m_orientation; }
	return glm::degrees(m_orientation); 
}


glm::vec2 Orientation::getOrientationAsNormalizedVector() const { return glm::rotate(glm::vec2{0.f, 1.f}, m_orientation); }


void Orientation::rotate(const float rotation, const bool unitIsRadians) {

	float toAdd{rotation};
	if(!unitIsRadians) { toAdd = glm::radians(rotation); }

	m_orientation += toAdd;
	normalizeOrientation();
}

void Orientation::setValue(const float value, const bool unitIsRadians) {

	float toSet{value};
	if(!unitIsRadians) { toSet = glm::radians(value); }

	m_orientation = toSet;
	normalizeOrientation();
} 



void Orientation::normalizeOrientation() {

	while (m_orientation < 0.f) { m_orientation = m_orientation + glm::pi<float>()*2.f; }
	while (m_orientation >= glm::pi<float>()*2.f)  { m_orientation = m_orientation - glm::pi<float>()*2.f; }
}

}

}