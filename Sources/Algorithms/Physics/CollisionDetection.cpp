#include "Algorithms/Physics/CollisionDetection.hpp"

namespace Gg {
namespace Algorithm {

CollisionDetection::CollisionDetection(GulgEngine &gulgEngine, std::vector<std::pair<Entity, Entity>> &collisionsToResolve): 
	AbstractAlgorithm{gulgEngine},
	m_collisionsToResolve{collisionsToResolve} {

	m_signature = gulgEngine.getComponentSignature("Hitbox");
}

CollisionDetection::~CollisionDetection() {}

void CollisionDetection::apply() {

	m_collisionsToResolve.clear();
	m_collisionsToResolve.reserve(m_entitiesToApply.size()*m_entitiesToApply.size());

	for(unsigned int i{0}; i < m_entitiesToApply.size(); i++) {

		std::shared_ptr<Component::CircleHitbox> firstHitbox{ 
			std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[i], "Hitbox"))
		};

		for(unsigned int j{i+1}; j < m_entitiesToApply.size(); j++) {

			std::shared_ptr<Component::CircleHitbox> secondHitbox{ 
				std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[j], "Hitbox"))
			};

			if(Maths::distance(firstHitbox->centerPosition, secondHitbox->centerPosition) 
			<= firstHitbox->radius + secondHitbox->radius) {

				m_collisionsToResolve.emplace_back(std::make_pair(m_entitiesToApply[i], m_entitiesToApply[j]));
			}

		}
	}
}

}}