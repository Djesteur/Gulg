#include "Algorithms/Physics/CollisionResolution.hpp"

namespace Gg {
namespace Algorithm {

CollisionResolution::CollisionResolution(GulgEngine &gulgEngine, std::vector<Collision> &collisionsToResolve): 
	AbstractAlgorithm{gulgEngine},
	m_collisionsToResolve{collisionsToResolve} {

	m_signature = gulgEngine.getComponentSignature("PhysicPosition");
	m_signature += gulgEngine.getComponentSignature("Mass");
}

CollisionResolution::~CollisionResolution() {}

void CollisionResolution::apply() {

	m_finalVector.clear();

	for(Collision currentCollision: m_collisionsToResolve) {

		std::shared_ptr<Component::UnsignedInt> firstMass{ 
			std::static_pointer_cast<Component::UnsignedInt>(m_gulgEngine.getComponent(currentCollision.firstEntity, "Mass"))
		};

		std::shared_ptr<Component::UnsignedInt> secondMass{ 
			std::static_pointer_cast<Component::UnsignedInt>(m_gulgEngine.getComponent(currentCollision.secondEntity, "Mass"))
		};

		float mass1{static_cast<float>(firstMass->value)},
			  mass2{static_cast<float>(secondMass->value)};

		float ratio{std::min(mass1, mass2)/(mass1 + mass2)};

		float firstRatio{0}, secondRatio{0};

		if(mass1 > mass2)  { 

			firstRatio = ratio;
			secondRatio = 1.f - ratio;
		}

		else { 

			firstRatio = 1.f - ratio;
			secondRatio = ratio;
		}

		if(m_finalVector.find(currentCollision.firstEntity) == m_finalVector.end()) {

			m_finalVector.insert(std::make_pair(currentCollision.firstEntity, Component::Vector2D{0.f, 0.f}));
		}

		if(m_finalVector.find(currentCollision.secondEntity) == m_finalVector.end()) {

			m_finalVector.insert(std::make_pair(currentCollision.secondEntity, Component::Vector2D{0.f, 0.f}));
		}

		m_finalVector[currentCollision.firstEntity].value += currentCollision.firstDirection.value*currentCollision.missingDistance*firstRatio;
		m_finalVector[currentCollision.secondEntity].value += currentCollision.secondDirection.value*currentCollision.missingDistance*secondRatio;
	}

	for(std::map<Entity, Component::Vector2D>::iterator it{m_finalVector.begin()}; it != m_finalVector.end(); it++) {

		std::shared_ptr<Component::Vector2D> position{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(it->first, "PhysicPosition"))
		};

		position->value += it->second.value;
	}
}


}}