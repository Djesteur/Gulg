#include "GulgInput/Action.hpp"

namespace Gg {

namespace Input {


Action::Action() {}

void Action::addEvent(const Event &event) {

	if(std::find(m_eventsThatTriggerAction.begin(), m_eventsThatTriggerAction.end(), event) == m_eventsThatTriggerAction.end()) { m_eventsThatTriggerAction.emplace_back(event); }
}

void Action::addCallback(std::function<void()> functionToCall) { m_callbacks.emplace_back(functionToCall); }

bool Action::operator==(const Action &second) {

	return m_eventsThatTriggerAction == second.m_eventsThatTriggerAction;
}

void Action::eventOccured(const Event &occuredEvent) {


	std::cout << "NB EVENT: " << m_eventsThatTriggerAction.size() << std::endl;

	if(std::find(m_eventsThatTriggerAction.begin(), m_eventsThatTriggerAction.end(), occuredEvent) != m_eventsThatTriggerAction.end()) {

			std::cout << "CALLBACK" << std::endl; 

		for(std::function<void()> &currentFunction: m_callbacks) { currentFunction(); }

	}
}



}

}