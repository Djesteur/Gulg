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




/**
 * @brief      The input updater register actions, group them, and triggers them when the update function found new events.
 */
class InputUpdater {

	public:



		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param      eventWindow  The SFML object that give us the inputs
		 */
		InputUpdater(sf::Window &eventWindow);



		/**
		 * @brief      Creates an group of action.
		 *
		 * @param[in]  groupName  The group name
		 */
		void createActionGroup(const std::string &groupName);



		/**
		 * @brief      Delete an existing group of action
		 *
		 * @param[in]  groupName  The group name
		 */
		void deleteActionGroup(const std::string &groupName);




		/**
		 * @brief      Check if a group of action with the given name already exist
		 *
		 * @param[in]  groupName  The group name to check
		 *
		 * @return     True if already exist, else false.
		 */
		bool actionGroupExist(const std::string &groupName) const;




		/**
		 * @brief      Active a group of action
		 *
		 * @param[in]  groupName  The group name
		 */
		void activateGroup(const std::string &groupName);



		/**
		 * @brief      Desactivate a groupe of action
		 *
		 * @param[in]  groupName  The group name
		 */
		void desactivateGroup(const std::string &groupName);



		/**
		 * @brief      Determines whether the specified group name is an activated group.
		 *
		 * @param[in]  groupName  The group name
		 *
		 * @return     True if the specified group name is an activated group, false otherwise.
		 */
		bool isActivatedGroup(const std::string &groupName);



		/**
		 * @brief      Creates an new action.
		 *
		 * @param[in]  groupName  The name of the group where this action will be added (by default, "Main")
		 *
		 * @return     The newly created action
		 */
		std::shared_ptr<Action> createAction(const std::string &groupName = "Main");



		/**
		 * @brief      Delete and existing action
		 *
		 * @param[in]  toDelete   To delete
		 * @param[in]  groupName  The name of the group where the action is (by default, "Main")
		 */
		void deleteAction(std::shared_ptr<Action> toDelete, const std::string &groupName = "Main");



		/**
		 * @brief      Check if the action already exist in a group
		 *
		 * @param[in]  toCheck    The action to check
		 * @param[in]  groupName  The name of the group
		 *
		 * @return     True if the action is present in the specified group,
		 *             false otherwise.
		 */
		bool actionIsInGroup(std::shared_ptr<Action> toCheck, const std::string &groupName);




		/**
		 * @brief      Updates the inputs.
		 *
		 * @return     A vector of events that aren't handled by the InputUpdater (because it's not implemented yet, or because it can't be)
		 */
		std::vector<Event> update();

	private:



		/**
		 * @brief      Return the list of new inputs since the last update
		 *
		 * @param      notHandledEvents  A reference to an array that will be fill with unhandled events
		 *
		 * @return     The list of new events that cna be handled
		 */
		std::vector<Event> detectInputChanges(std::vector<Event> &notHandledEvents);



		/**
		 * @brief      Check if a button if pressed for the first time or not
		 *
		 * @param[in]  alreadyTakeInCountEvents  The already take in count events. If the PressedButton event was triggered this update, it must be in this array.
		 *
		 * @return     A ButtonStillPressed event if it's not the first time, else and Unknown event
		 */
		std::vector<Event> checkIfStillPressed(const std::vector<Event> &alreadyTakeInCountEvents) const;



		/**
		 * @brief      Check if the event if a ButttonPressed Event
		 *
		 * @param[in]  key   The sf::Keyboard::Key that has been pressed
		 *
		 * @return     A ButtonPressed event or a Unknown event, depending of the previous state of the button
		 */
		Event pressedKeyboardKey(const sf::Keyboard::Key &key);


		/**
		 * @brief      Check if the event if a ButttonReleased Event
		 *
		 * @param[in]  key   The sf::Keyboard::Key that has been released
		 *
		 * @return     A ButtonReleased event or a Unknown event, depending of the previous state of the button
		 */
		Event releasedKeyboardKey(const sf::Keyboard::Key &key);

		std::map<std::string, std::vector<std::shared_ptr<Action>>> m_actions;
		std::vector<std::string> m_groupsToTrigger;


		sf::Window &m_eventWindow;
		std::map<sf::Keyboard::Key, bool> m_keyboardState;

};

}}

#endif