#include "Algorithms/Graphics/AnimationUpdate.hpp"

namespace Gg {
namespace Algorithm {

AnimationUpdate::AnimationUpdate(const std::string componentName, GulgEngine &gulgEngine): 
	SpecializedAlgorithm{componentName, gulgEngine} {

		m_signature += gulgEngine.getComponentSignature("GraphicPosition");
		m_lastTimePoint = std::chrono::steady_clock::now();
	}

AnimationUpdate::~AnimationUpdate() {}

void AnimationUpdate::resetTime() { m_lastTimePoint = std::chrono::steady_clock::now(); }

void AnimationUpdate::apply() {

	std::chrono::time_point<std::chrono::steady_clock> nowTimePoint{std::chrono::steady_clock::now()};

	const long int elapsedMicroseconds{std::chrono::duration_cast<std::chrono::microseconds>(nowTimePoint - m_lastTimePoint).count()};

	m_lastTimePoint = nowTimePoint;

	for(Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Component::AnimationSet> animationSet{ 
			std::static_pointer_cast<Component::AnimationSet>(m_gulgEngine.getComponent(currentEntity, m_componentToApply))
		};

		//Timer update

		animationSet->timer.localElapsedMicroseconds += elapsedMicroseconds;

		while(animationSet->timer.localElapsedMicroseconds >= animationSet->timerLimit) {

			animationSet->timer.localElapsedMicroseconds -= animationSet->timerLimit;
			animationSet->timer.nbTrigger++;

		}

		// Animation update

		if(animationSet->timer.nbTrigger != 0) {

			while(animationSet->timer.nbTrigger > 0) { 
				
				animationSet->animations[animationSet->currentAnimation].nextFrame();
				animationSet->timer.nbTrigger--;
			}

			animationSet->sprite.setTextureRect(animationSet->animations[animationSet->currentAnimation]
											   .frames[animationSet->animations[animationSet->currentAnimation].currentFrame]);
		}

		//Animation position

		std::shared_ptr<Component::Vector2D> animationPosition{ 
			std::static_pointer_cast<Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "GraphicPosition"))
		};

		animationSet->sprite.setPosition(animationPosition->value);
	}
}

}}