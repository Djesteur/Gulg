#ifndef INPUT_UPDATER
#define INPUT_UPDATER

#include <string>
#include <map>

#include <memory>

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

		std::shared_ptr<Action> createAction(const std::string &groupName);
		void deleteAction(std::shared_ptr<Action> toDelete, const std::string &groupName);
		bool actionIsInGroup(std::shared_ptr<Action> toCheck, const std::string &groupName);

		void update();

	private:

		std::map<std::string, std::vector<std::shared_ptr<Action>>> m_actions;
		std::vector<std::string> m_groupsToTrigger;

};

}}

#endif