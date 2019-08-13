#include "Algorithms/Physics/PositionUpdate.hpp"

namespace Gg {
namespace Algorithm {

PositionUpdate::PositionUpdate(GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine} {

		m_signature = gulgEngine.getComponentSignature("PhysicPosition");
		m_signature += gulgEngine.getComponentSignature("Speed");
		m_signature += gulgEngine.getComponentSignature("Mass");
}

PositionUpdate::~PositionUpdate() {}

void PositionUpdate::apply() {}

void PositionUpdate::apply(const long unsigned int elapsedTime) {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::Vector2D> position{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "PhysicPosition"))
		};

		std::shared_ptr<Component::Vector2D> speed{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "Speed"))
		};

		std::shared_ptr<Component::UnsignedInt> mass{ 
			std::static_pointer_cast<Component::UnsignedInt>(m_gulgEngine.getComponent(currentEntity, "Mass"))
		};

		position->value += speed->value*(elapsedTime/1'000'000.f); // Because time is in microsecond and we have time in meter/second
	}
}

}}