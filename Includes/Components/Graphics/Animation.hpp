#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Animation: public AbstractComponent {

	enum class Type {

		Classic,
		NormalReapeat,
		ReverseRepeat
	};

	Animation(): currentFrame{0}, cameBack{false}, name{""}, timer{100} {}

	Animation(const Animation &animation): 
		currentFrame{animation.currentFrame},
		cameBack{animation.cameBack},
		frames{animation.frames},
		animationType{animation.animationType},
		name{animation.name},
		timer{animation.timer} {}

	void nextFrame() {

		switch(animationType) {

			case Type::Classic:
				currentFrame++;
				if(currentFrame >= frames.size()) { currentFrame = frames.size() - 1; }
				break;

			case Type::NormalReapeat:
				currentFrame++;
				if(currentFrame >= frames.size()) { currentFrame = 0; }
				break;

			case Type::ReverseRepeat:

				if(!cameBack) { 

					currentFrame++;
					if(currentFrame >= frames.size()) { 
						currentFrame = frames.size() - 2;
						cameBack = true;
					}
				}

				else {
					
					currentFrame--;

					if(currentFrame == 0) { cameBack = false; }
				}
				break;
		}
	}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Animation>(*this)); }

	unsigned int currentFrame;
	bool cameBack;
	std::vector<sf::IntRect> frames;
	Type animationType;
	std::string name;
	unsigned int timer;
	
};

}}

#endif