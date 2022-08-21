#include "GulgInput/InputUpdater.hpp"


namespace Gg {

namespace Input {

InputUpdater::InputUpdater(sf::Window &eventWindow): m_eventWindow{eventWindow} {

	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::A, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::B, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::C, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::D, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::E, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::G, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::H, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::I, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::J, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::K, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::L, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::M, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::N, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::O, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::P, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Q, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::R, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::S, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::T, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::U, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::V, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::W, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::X, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Y, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Z, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num0, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num1, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num2, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num3, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num4, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num5, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num6, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num7, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num8, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Num9, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Escape, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::LControl, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::LShift, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::LAlt, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::LSystem, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::RControl, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::RShift, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::RAlt, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::RSystem, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Menu, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::LBracket, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::RBracket, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Semicolon, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Comma, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Period, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Quote, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Slash, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Backslash, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Tilde, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Equal, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Hyphen, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Space, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Enter, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Backspace, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Tab, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::PageUp, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::PageDown, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::End, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Home, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Insert, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Delete, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Add, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Subtract, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Multiply, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Divide, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Left, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Right, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Up, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Down, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad0, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad1, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad2, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad3, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad4, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad5, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad6, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad7, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad8, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Numpad9, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F1, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F2, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F3, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F4, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F5, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F6, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F7, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F8, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F9, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F10, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F11, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F12, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F13, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F14, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::F15, false));
	m_keyboardState.insert(std::make_pair(sf::Keyboard::Key::Pause, false));
}

void InputUpdater::createActionGroup(const std::string &groupName) {

	if(!actionGroupExist(groupName)) { 

		m_actions.insert(std::make_pair(groupName, std::vector<std::shared_ptr<Action>>{}));
		activateGroup(groupName);
	}
}

void InputUpdater::deleteActionGroup(const std::string &groupName) {

	if(actionGroupExist(groupName)) { 

		desactivateGroup(groupName);
		m_actions.erase(groupName); 
	}
}

bool InputUpdater::actionGroupExist(const std::string &groupName) const { return m_actions.find(groupName) != m_actions.end(); }


void InputUpdater::activateGroup(const std::string &groupName) {

	if(std::find(m_groupsToTrigger.begin(), m_groupsToTrigger.end(), groupName) == m_groupsToTrigger.end()) { m_groupsToTrigger.emplace_back(groupName); }
}

void InputUpdater::desactivateGroup(const std::string &groupName) {

	std::vector<std::string>::iterator foundInTrigger = std::find(m_groupsToTrigger.begin(), m_groupsToTrigger.end(), groupName);
	if(foundInTrigger != m_groupsToTrigger.end()) { m_groupsToTrigger.erase(foundInTrigger); }

}

bool InputUpdater::isActivatedGroup(const std::string &groupName) { return std::find(m_groupsToTrigger.begin(), m_groupsToTrigger.end(), groupName) != m_groupsToTrigger.end(); }


std::shared_ptr<Action> InputUpdater::createAction(const std::string &groupName) {

	if(!actionGroupExist(groupName)) { createActionGroup(groupName); }
	m_actions[groupName].emplace_back(std::make_shared<Action>());

	return m_actions[groupName].back();
}

void InputUpdater::deleteAction(std::shared_ptr<Action> toDelete, const std::string &groupName) {

	if(!actionGroupExist(groupName)) { return; }

	std::vector<std::shared_ptr<Action>>::iterator foundInActions = std::find(m_actions[groupName].begin(), m_actions[groupName].end(), toDelete);
	if(foundInActions != m_actions[groupName].end()) { m_actions[groupName].erase(foundInActions); }
}

bool InputUpdater::actionIsInGroup(std::shared_ptr<Action> toCheck, const std::string &groupName) {

	if(!actionGroupExist(groupName)) { return false; }
	return std::find(m_actions[groupName].begin(), m_actions[groupName].end(), toCheck) != m_actions[groupName].end();
}

std::vector<Event> InputUpdater::update() {


	std::vector<Event> notHandledEvents;

	std::vector<Event> occuredEvents = detectInputChanges(notHandledEvents);

	//Send them in the actions

	for(const Event &currentEvent: occuredEvents) { 

		for(const std::string &currentGroup: m_groupsToTrigger) {

			for(std::shared_ptr<Action> currentAction: m_actions[currentGroup]) { currentAction->eventOccured(currentEvent); }
		}
	}

	return notHandledEvents;
}

std::vector<Event> InputUpdater::detectInputChanges(std::vector<Event> &notHandledEvents) {

	std::vector<Event> newEvents;

	std::vector<sf::Event> newSFMLEvents;

	sf::Event SFMLEventToPoll;

	while(m_eventWindow.pollEvent(SFMLEventToPoll)) { newSFMLEvents.emplace_back(SFMLEventToPoll); }

	for(sf::Event currentSFMLEvent: newSFMLEvents) {

		switch(currentSFMLEvent.type) {

			//Window

			case sf::Event::Closed:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::WindowClosed});
				break;

			case sf::Event::Resized:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::WindowResized});
				break;

			case sf::Event::LostFocus:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::WindowLostFocus});
				break;

			case sf::Event::GainedFocus:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::WindowGainedFocus});
				break;

			//Keyboard
			case sf::Event::KeyPressed:
				newEvents.emplace_back(pressedKeyboardKey(currentSFMLEvent.key.code));
				break;

			case sf::Event::KeyReleased:
				newEvents.emplace_back(releasedKeyboardKey(currentSFMLEvent.key.code));
				break;

			//Mouse
			case sf::Event::MouseWheelMoved:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseWheelScrolled:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseButtonPressed:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseButtonReleased:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseMoved:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseEntered:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::MouseLeft:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			//Joystick

			case sf::Event::JoystickButtonPressed:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::JoystickButtonReleased:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::JoystickMoved:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::JoystickConnected:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::JoystickDisconnected:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			//Pad
			case sf::Event::TouchBegan:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::TouchMoved:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

			case sf::Event::TouchEnded:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::NotImplementedYet});
				break;

				//Unknown

			default:
				notHandledEvents.emplace_back(Event{HandledInput::Unknown, EventType::Unknown});
				break;
		}
	}

	std::vector<Event> stillPressedEvents = checkIfStillPressed(newEvents);
	newEvents.insert(newEvents.end(), stillPressedEvents.begin(), stillPressedEvents.end());

	return newEvents;
}

std::vector<Event> InputUpdater::checkIfStillPressed(const std::vector<Event> &alreadyTakeInCountEvents) const {

	std::vector<Event> stillPressedEvents;


	for(std::pair<sf::Keyboard::Key, bool> currentEventState: m_keyboardState) {

		if(sf::Keyboard::isKeyPressed(currentEventState.first) && currentEventState.second) { 

			HandledInput currentInput = getGulgFromSFMLKey(currentEventState.first);

			bool alreadyTakeInCount{false};

			for(const Event &currentTakeInCountEvent: alreadyTakeInCountEvents) {

				if(currentTakeInCountEvent.handledInput == currentInput) { alreadyTakeInCount = true; break; }
			}

			if(!alreadyTakeInCount) { stillPressedEvents.emplace_back(getGulgFromSFMLKey(currentEventState.first), EventType::ButtonStillPressed); }
		}

	}

	return stillPressedEvents;
}

Event InputUpdater::pressedKeyboardKey(const sf::Keyboard::Key &key) {

	//Not handled event
	if(m_keyboardState.find(key) == m_keyboardState.end()) { return Event{HandledInput::Unknown, EventType::Unknown}; }

	//Repetition of the event, handled in checkIfStillPressed
	if(m_keyboardState[key]) { return Event{getGulgFromSFMLKey(key), EventType::Unknown}; }

	m_keyboardState[key] = true;
	return Event{getGulgFromSFMLKey(key), EventType::ButtonPressed};
}

Event InputUpdater::releasedKeyboardKey(const sf::Keyboard::Key &key) {

	//Not handled event
	if(m_keyboardState.find(key) == m_keyboardState.end()) { return Event{HandledInput::Unknown, EventType::Unknown}; }

	//Take this in count ?
	// if(!m_keyboardState[key]) { ERROR }

	m_keyboardState[key] = false;

	return Event{getGulgFromSFMLKey(key), EventType::ButtonReleased};
}


}

}