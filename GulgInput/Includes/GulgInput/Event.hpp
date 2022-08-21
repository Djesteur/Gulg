#ifndef EVENT_HPP
#define EVENT_HPP

#include <SFML/Window/Keyboard.hpp>

namespace Gg {

namespace Input {



/**
 * @brief      This class describes an event type.
 */

enum class EventType {

	Unknown,
	NotImplementedYet,
	ButtonPressed,
	ButtonStillPressed,
	ButtonReleased,
	WindowClosed,
	WindowResized,
	WindowLostFocus,
	WindowGainedFocus
};



/**
 * @brief      This class describes a handled input.
 */

enum class HandledInput {

	Unknown,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Num0,
	Num1,
	Num2,
	Num3,
	Num4,
	Num5,
	Num6,
	Num7,
	Num8,
	Num9,
	Escape,
	LeftControl,
	LeftShift,
	LeftAlt,
	LeftSystem,
	RightControl,
	RightShift,
	RightAlt,
	RightSystem,
	Menu,
	LeftBracket,
	RightBracket,
	Semicolon,
	Comma,
	Period,
	Quote,
	Slash,
	Backslash,
	Tilde,
	Equal,
	Hyphen,
	Space,
	Enter,
	Backspace,
	Tab,
	PageUp,
	PageDown,
	End,
	Home,
	Insert,
	Delete,
	Add,
	Subtract,
	Multiply,
	Divide,
	Left,
	Right,
	Up,
	Down,
	Numpad0,
	Numpad1,
	Numpad2,
	Numpad3,
	Numpad4,
	Numpad5,
	Numpad6,
	Numpad7,
	Numpad8,
	Numpad9,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15, 
	Pause
};




/**
 * @brief      Represent an input event
 */
struct Event {



	/**
	 * @brief      Constructs a new instance.
	 *
	 * @param[in]  hi    The HandledInput
	 * @param[in]  et    The EventType
	 */
	Event(const HandledInput &hi = HandledInput::Unknown, const EventType &et = EventType::Unknown): handledInput{hi}, eventType{et} {}



	/**
	 * @brief      The button/axis/device that changed since last update
	 */
	HandledInput handledInput;

	/**
	 * @brief      What appened to the handledInput.
	 */
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



/**
 * @brief      Gets the sf::Keyboard::Key from a Gulg::HandledInput.
 *
 * @param[in]  handledInput  The input to convert
 *
 * @return     The corresponding sf::Keyboard::Key.
 */
sf::Keyboard::Key getSFMLFromGulgKey(const HandledInput &handledInput);



/**
 * @brief      Gets the Gulg::HandledInput from a sf::Keyboard::Key.
 *
 * @param[in]  key   The input to convert
 *
 * @return     The corresponding Gulg::HandledInput.
 */
HandledInput getGulgFromSFMLKey(const sf::Keyboard::Key &key);


}}

#endif