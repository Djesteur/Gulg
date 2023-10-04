#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include <glm/vec2.hpp>

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

/**
 * @brief      Component for a position
 */

class Position: public AbstractComponent {

	public:

		/**
		 * @brief      Default constructor
		 */

		Position();


		/**
		 * @brief      Constructs a new instance with X and y members
		 *
		 * @param[in]  x     The X position
		 * @param[in]  y     The Y position
		 */
		Position(const float x, const float y);


		/**
		 * @brief      Constructs a new instance from an already existing vector
		 *
		 * @param[in]  position  The position
		 */

		Position(const glm::vec2 position);

		/**
		 * @brief      Sets the position.
		 *
		 * @param[in]  newX  The new x
		 * @param[in]  newY  The new y
		 */

		void setPosition(const float newX, const float newY);

		/**
		 * @brief      Sets the position.
		 *
		 * @param[in]  newPosition  The new position
		 */
		void setPosition(const glm::vec2 newPosition);

		/**
		 * @brief      Add X and Y to the current value
		 *
		 * @param[in]  x     The X value
		 * @param[in]  y     The Y value
		 */

		void move(const float x, const float y);

		/**
		 * @brief      Add movement to the position
		 *
		 * @param[in]  movement  The movement to add
		 */
		void move(const glm::vec2 movement);


		/**
		 * @brief      Gets the x value.
		 *
		 * @return     The x.
		 */

		float getX() const;

		/**
		 * @brief      Gets the y value.
		 *
		 * @return     The y.
		 */
		float getY() const;

		/**
		 * @brief      Gets the position.
		 *
		 * @return     The position.
		 */
		glm::vec2 getPosition() const;

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */

		virtual std::shared_ptr<AbstractComponent> clone() const;

		STATIC_GET_TYPE(Position)

		glm::vec2 m_position;
};

}}

#endif