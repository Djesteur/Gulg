#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>

#include "GulgInput/Event.hpp"

namespace Gg {

namespace Input {


class InputUpdater;

/**
 * @brief   A link between an event and the functions to call
 * @details Add the functions and the event that will trigger this action.
 */

class Action {

	public:



		/**
		 * @brief      Constructs a new instance.
		 *
		 */

		Action();

		void addEvent(const Event event);
		void addCallback(std::function<void()> functionToCall);

		bool operator==(const Action &second);

	private:

		friend class InputUpdater;
		void eventOccured(const Event occuredEvent);

		std::vector<Event> m_eventsThatTriggerAction;
		std::vector<std::function<void()>> m_callbacks;

};

}}

#endif