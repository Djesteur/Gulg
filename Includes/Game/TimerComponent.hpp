#ifndef TIMER_COMPONENT_HPP
#define TIMER_COMPONENT_HPP

#include "Component.hpp"

namespace Gg {

struct TimerComponent: public Component {

	TimerComponent():
		nbTrigger{0},
		localElapsedMicroseconds{0},
		timeLimit{1} {}

	TimerComponent(const long int limit):
		nbTrigger{0},
		localElapsedMicroseconds{0},
		timeLimit{limit} {}

	TimerComponent(const TimerComponent &timerComponent):
		nbTrigger{timerComponent.nbTrigger},
		localElapsedMicroseconds{timerComponent.localElapsedMicroseconds},
		timeLimit{timerComponent.timeLimit} {}

	virtual std::shared_ptr<Component> clone() const { return std::static_pointer_cast<Component>(std::make_shared<TimerComponent>(*this)); }

	unsigned int nbTrigger;
	long int localElapsedMicroseconds;
	const long int timeLimit;          
};

}

#endif