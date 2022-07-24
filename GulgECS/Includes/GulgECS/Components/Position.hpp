#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

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
		 * @brief      Constructor with values
		 *
		 * @param[in]  x     The X position
		 * @param[in]  y     The Y position
		 */
		Position(double x, double y);

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */

		virtual std::shared_ptr<AbstractComponent> clone() const;

		STATIC_GET_TYPE(Position)

		/// X position
		double X;

		/// Y Position
		double Y;
};

}}

#endif