#include "Algorithms/Graphics/DrawAnimationSet.hpp"

namespace Gg {

namespace Algorithm {

DrawAnimationSet::DrawAnimationSet(sf::RenderTarget &renderTarget, 
								   const std::string componentName,
								   GulgEngine &gulgEngine): 

	SpecializedAlgorithm{componentName, gulgEngine},
	m_renderTarget{renderTarget} {}

DrawAnimationSet::~DrawAnimationSet() {}

void DrawAnimationSet::apply() {

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::AnimationSet> currentComponent{ 
			std::static_pointer_cast<Component::AnimationSet>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		m_renderTarget.draw(currentComponent->sprite);
	}
}

}}