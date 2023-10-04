#include "GulgECS/Components/Mass.hpp"

namespace Gg {

namespace Component {

Mass::Mass(): 
	m_mass{1.0},
	m_canBeMoved{true} {}


Mass::Mass(const float mass, const bool canBeMoved ):
	m_mass{mass},
	m_canBeMoved{canBeMoved} {}

		
float Mass::getMass() const { return m_mass; }
void Mass::setMass(const float newMass, const bool canBeMoved) {

	m_mass = newMass;
	m_canBeMoved = canBeMoved;
}

bool Mass::canBeMoved() const { return m_canBeMoved; }


std::shared_ptr<AbstractComponent> Mass::clone() const { return std::make_shared<Mass>(m_mass, m_canBeMoved); }

}

}