#ifndef INPUT_UPDATER
#define INPUT_UPDATER

#include <string>
#include <map>

#include <iostream>

#include "GulgInput/Action.hpp"
#include "GulgInput/Event.hpp"

namespace Gg {

namespace Input {

class InputUpdater {

	public:


		InputUpdater();

		void createActionGroup(const std::string &groupName);
		void deleteActionGroup(const std::string &groupName);
		bool actionGroupExist(const std::string &groupName) const;

		void activateGroup(const std::string &groupName);
		void desactivateGroup(const std::string &groupName);
		bool isActivatedGroup(const std::string &groupName);

		Action &createAction(const std::string &groupName);
		void deleteAction(const Action &toDelete, const std::string &groupName);
		bool actionIsInGroup(const Action &toCheck, const std::string &groupName);

		void update();

	private:

		std::map<std::string, std::vector<Action>> m_actions;
		std::vector<std::string> m_groupsToTrigger;

};

}}

#endif