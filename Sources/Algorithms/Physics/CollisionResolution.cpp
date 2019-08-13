#include "Algorithms/Physics/CollisionResolution.hpp"

namespace Gg {
namespace Algorithm {

CollisionResolution::CollisionResolution(GulgEngine &gulgEngine, std::vector<std::pair<Entity, Entity>> &collisionsToResolve): 
	AbstractAlgorithm{gulgEngine},
	m_collisionsToResolve{collisionsToResolve} {

	m_signature = gulgEngine.getComponentSignature("PhysicPosition");
	m_signature += gulgEngine.getComponentSignature("Mass");
}

CollisionResolution::~CollisionResolution() {}

void CollisionResolution::apply() {

	std::map<Entity, Component::Vector2D> finalVector;

	for(std::pair<Entity, Entity> currentCollision: m_collisionsToResolve) {

		std::shared_ptr<Component::CircleHitbox> first{ 
			std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(currentCollision.first, "Hitbox"))
		};

		std::shared_ptr<Component::CircleHitbox> second{ 
			std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(currentCollision.second, "Hitbox"))
		};

		std::shared_ptr<Component::Vector2D> firstPosition{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentCollision.first, "PhysicPosition"))
		};

		std::shared_ptr<Component::Vector2D> secondPosition{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentCollision.second, "PhysicPosition"))
		};

		Component::Vector2D firstToSecond{Maths::vectorFromPoints(firstPosition->value, secondPosition->value)};
		Component::Vector2D secondToFirst{Maths::vectorFromPoints(secondPosition->value, firstPosition->value)};

		float distanceBetweenPoints{firstToSecond.norm()};

		firstToSecond.value /= firstToSecond.norm();
		secondToFirst.value /= secondToFirst.norm();
		std::shared_ptr<Component::UnsignedInt> firstMass{ 
			std::static_pointer_cast<Component::UnsignedInt>(m_gulgEngine.getComponent(currentCollision.first, "Mass"))
		};

		std::shared_ptr<Component::UnsignedInt> secondMass{ 
			std::static_pointer_cast<Component::UnsignedInt>(m_gulgEngine.getComponent(currentCollision.second, "Mass"))
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

		float missingDistance{first->radius + second->radius - distanceBetweenPoints};

		if(finalVector.find(currentCollision.first) == finalVector.end()) {

			finalVector.insert(std::make_pair(currentCollision.first, Component::Vector2D{0.f, 0.f}));
		}

		if(finalVector.find(currentCollision.second) == finalVector.end()) {

			finalVector.insert(std::make_pair(currentCollision.second, Component::Vector2D{0.f, 0.f}));
		}

		finalVector[currentCollision.first].value += secondToFirst.value*missingDistance*firstRatio;
		finalVector[currentCollision.second].value += firstToSecond.value*missingDistance*secondRatio;
	}

	for(std::map<Entity, Component::Vector2D>::iterator it{finalVector.begin()}; it != finalVector.end(); it++) {

		std::shared_ptr<Component::Vector2D> position{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(it->first, "PhysicPosition"))
		};

		position->value += it->second.value;
	}
}

}}