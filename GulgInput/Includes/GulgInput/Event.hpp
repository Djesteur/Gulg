#ifndef EVENT_HPP
#define EVENT_HPP

namespace Gg {

namespace Input {



/**
 * @brief      This class describes an event type.
 */

enum class EventType {

	ButtonPressed,
	ButtonStillPressed,
	ButtonReleased,
	AxeBeginMove,
	AxeMoving,
	AxeStopMove,
	Unknown
};



/**
 * @brief      This class describes a handled input.
 */

enum class HandledInput {

	Z,
	Q,
	S,
	D,
	Mouse,
	Unknown
};




/**
 * @brief      Represent an input event
 */
struct Event {

	Event(const HandledInput &hi = HandledInput::Unknown, const EventType &et = EventType::Unknown): handledInput{hi}, eventType{et} {}

	HandledInput handledInput;
	EventType eventType;
};



/**
 * @brief      Equality operator between two events.
 *
 * @param[in]  firstEvent   The first event
 * @param[in]  secondEvent  The second event
 *
 * @return     The result of the equality
 */
bool operator==(const Event &firstEvent, const Event &secondEvent);


}}

#endif