#include "Algorithms/SynchronizePositions.hpp"

namespace Gg {
namespace Algorithm {

SynchronizePositions::SynchronizePositions(GulgEngine &gulgEngine, const unsigned int pixelPerMeter): 
	AbstractAlgorithm{gulgEngine},
	m_pixelPerMeter{pixelPerMeter} {

	m_signature = gulgEngine.getComponentSignature("PhysicPosition");
	m_signature += gulgEngine.getComponentSignature("GraphicPosition");
	m_signature += gulgEngine.getComponentSignature("Hitbox");
	m_signature += gulgEngine.getComponentSignature("GraphicHitbox");
}

SynchronizePositions::~SynchronizePositions() {}

void SynchronizePositions::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::Vector2D> graphic{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "GraphicPosition"))
		};

		std::shared_ptr<Component::Vector2D> physic{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "PhysicPosition"))
		};

		std::shared_ptr<Component::AbstractHitbox> hitbox{ 
			std::static_pointer_cast<Component::AbstractHitbox>(m_gulgEngine.getComponent(currentEntity, "Hitbox"))
		};

		std::shared_ptr<Component::Shape> graphicHitbox{ 
			std::static_pointer_cast<Component::Shape>(m_gulgEngine.getComponent(currentEntity, "GraphicHitbox"))
		};

		graphic->value = sf::Vector2f{physic->value.x*m_pixelPerMeter, physic->value.y*m_pixelPerMeter};
		hitbox->centerPosition.value = physic->value;
		graphicHitbox->shape->setPosition(graphic->value);
	}
}

}}