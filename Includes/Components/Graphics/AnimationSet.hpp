#ifndef ANIMATION_SET_HPP
#define ANIMATION_SET_HPP

#include <string>
#include <sstream>
#include <memory>

#include "Libraries/tinyxml2.h"

#include "GulgEngine/GulgDeclarations.hpp"
#include "GulgEngine/GulgEngine.hpp"

#include "Components/Component.hpp"
#include "Components/BasicComponents.hpp"
#include "Components/Graphics/Animation.hpp"
#include "Components/Game/Timer.hpp"

namespace Gg {

namespace Component {

struct AnimationSet: public AbstractComponent {

	public:

		AnimationSet(): name{""}, timerLimit{0}, currentAnimation{0} {}

		AnimationSet(const AnimationSet &animationSet):
			animations{animationSet.animations},
			name{animationSet.name},
			timer{animationSet.timer},
			timerLimit{animationSet.timerLimit},
			currentAnimation{animationSet.currentAnimation} {

			sprite.setTexture(*animationSet.sprite.getTexture());
			sprite.setTextureRect(animations.back().frames[0]);
		}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<AnimationSet>(*this)); }
		
		bool loadFromFile(GulgEngine &engine, const std::string path);

		bool changeAnimation(const std::string nextAnimation);
		bool changeAnimation(const unsigned int nextAnimation);

		std::vector<Animation> animations;
		std::string name;
		Timer timer;
		unsigned int timerLimit;
		unsigned int currentAnimation;
		sf::Sprite sprite;

	private:

		Animation loadAnimationFromXML(tinyxml2::XMLElement *currentAnimation);
};

}}

#endif