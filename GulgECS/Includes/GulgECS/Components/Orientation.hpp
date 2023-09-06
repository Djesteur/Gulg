#ifndef ORIENTATION_COMPONENT_HPP
#define ORIENTATION_COMPONENT_HPP

#include <glm/vec2.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/constants.hpp>

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

/**
 * @brief      Component for a position
 */

class Orientation: public AbstractComponent {

	public:

		/**
		 * @brief      Default constructor
		 */

		Orientation();


		/**
		 * @brief      Constructor with values
		 *
		 * @param[in]  orientation     The orientation, degree
		 */
		Orientation(const float orientation, const bool unitIsRadians = true);

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */

		virtual std::shared_ptr<AbstractComponent> clone() const;

		/**
		 * @brief      Gets the orientation, as radians
		 *
		 * @return     The orientation.
		 */

		float getOrientation(const bool unitIsRadians = true) const;

		/**
		 * @brief      Gets as normalized vector.
		 *
		 * @return     A normalized vector oriented.
		 */
		glm::vec2 getOrientationAsNormalizedVector() const;

		/**
		 * @brief      Rotate the orientation
		 *
		 * @param[in]  rotation  The rotation
		 */

		void rotate(const float rotation, const bool unitIsRadians = true);

		/**
		 * @brief      Sets the orientation.
		 *
		 * @param[in]  value  The new orientation
		 */
		void setValue(const float value, const bool unitIsRadians = true); 

		STATIC_GET_TYPE(Orientation)

		/// Orientation 
		float m_orientation;

	private:

		/**
		 * @brief      Make the value of orientation between 0 and 360°
		 */

		void normalizeOrientation();
};

}}

#endif