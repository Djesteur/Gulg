#include "GulgInput/InputUpdater.hpp"


namespace Gg {

namespace Input {

InputUpdater::InputUpdater() {}

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

void InputUpdater::update() {

	//Create new inputs

	std::vector<Event> occuredEvents;

	Event newEvent;
	newEvent.handledInput = HandledInput::Z;
	newEvent.eventType = EventType::ButtonPressed;
	occuredEvents.emplace_back(newEvent);

	//Send them in the actions

	for(const Event &currentEvent: occuredEvents) { 

		for(const std::string &currentGroup: m_groupsToTrigger) {

			for(std::shared_ptr<Action> currentAction: m_actions[currentGroup]) { 

				currentAction->eventOccured(currentEvent);
			}
		}
	}

}

}

}