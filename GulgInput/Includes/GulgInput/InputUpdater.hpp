#ifndef INPUT_UPDATER
#define INPUT_UPDATER

#include <string>
#include <map>

#include <memory>

#include <SFML/Window.hpp>

#include "GulgInput/Action.hpp"
#include "GulgInput/Event.hpp"

namespace Gg {

namespace Input {

class InputUpdater {

	public:


		InputUpdater(sf::Window &eventWindow);

		void createActionGroup(const std::string &groupName);
		void deleteActionGroup(const std::string &groupName);
		bool actionGroupExist(const std::string &groupName) const;

		void activateGroup(const std::string &groupName);
		void desactivateGroup(const std::string &groupName);
		bool isActivatedGroup(const std::string &groupName);

		std::shared_ptr<Action> createAction(const std::string &groupName);
		void deleteAction(std::shared_ptr<Action> toDelete, const std::string &groupName);
		bool actionIsInGroup(std::shared_ptr<Action> toCheck, const std::string &groupName);

		std::vector<Event> update();

	private:

		std::vector<Event> detectInputChanges(std::vector<Event> &notHandledEvents);
		std::vector<Event> checkIfStillPressed(const std::vector<Event> &alreadyTakeInCountEvents) const;

		Event pressedKeyboardKey(const sf::Keyboard::Key &key);
		Event releasedKeyboardKey(const sf::Keyboard::Key &key);

		std::map<std::string, std::vector<std::shared_ptr<Action>>> m_actions;
		std::vector<std::string> m_groupsToTrigger;


		sf::Window &m_eventWindow;
		std::map<sf::Keyboard::Key, bool> m_keyboardState;

};

}}

#endif