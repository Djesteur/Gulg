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




		/**
		 * @brief      Adds an event that will trigger this action when it append.
		 *
		 * @param[in]  event  The event to add
		 */
		void addEvent(const Event event);




		/**
		 * @brief      Adds a callback function to call when this action is triggered.
		 *
		 * @param[in]  functionToCall  The function to call
		 */
		void addCallback(std::function<void()> functionToCall);



		/**
		 * @brief      Equality operator.
		 *
		 * @param[in]  second  The second
		 *
		 * @return     The result of the equality
		 */
		bool operator==(const Action &second);

	private:

		friend class InputUpdater;

		/**
		 * @brief      Test if the the event that just occured can trigger this action. If yes, the callback functions are called.
		 *
		 * @param[in]  occuredEvent  The occured event
		 */
		void eventOccured(const Event occuredEvent);

		std::vector<Event> m_eventsThatTriggerAction;
		std::vector<std::function<void()>> m_callbacks;

};

}}

#endif