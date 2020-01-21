#ifndef TIMER_COMPONENT_HPP
#define TIMER_COMPONENT_HPP

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct Timer: public AbstractComponent {

	Timer():
		nbTrigger{0},
		localElapsedMicroseconds{0},
		timeLimit{1},
		isStopped{false} {}

	Timer(long int limit):
		nbTrigger{0},
		localElapsedMicroseconds{0},
		timeLimit{limit},
		isStopped{false} {}

	Timer(const Timer &timerComponent):
		nbTrigger{timerComponent.nbTrigger},
		localElapsedMicroseconds{timerComponent.localElapsedMicroseconds},
		timeLimit{timerComponent.timeLimit},
		isStopped{timerComponent.isStopped} {}

	virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<Timer>(*this)); }

	void reset() {

		nbTrigger = 0;
		localElapsedMicroseconds = 0;
	}

	unsigned int nbTrigger;
	long int localElapsedMicroseconds;
	long int timeLimit;
	bool isStopped;          
};

}}

#endif