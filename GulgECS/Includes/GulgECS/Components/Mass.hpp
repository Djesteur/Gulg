#ifndef MASS_COMPONENT_HPP
#define MASS_COMPONENT_HPP

#include <glm/vec2.hpp>

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {

namespace Component {

/**
 * @brief      Component for a position
 */

class Mass: public AbstractComponent {

	public:

		/**
		 * @brief      Default constructor
		 */

		Mass();


		/**
		 * @brief      Constructor with values
		 *
		 * @param[in]  Mass     The Mass, degree
		 */
		Mass(const float mass = 1.0, const bool canBeMoved = true);


		float getMass() const;
		void setMass(const float newMass, const bool canBeMoved = true);
		bool canBeMoved() const;

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */

		virtual std::shared_ptr<AbstractComponent> clone() const;


		STATIC_GET_TYPE(Mass)

		/// Mass 
		float m_mass;

		bool m_canBeMoved;
};

}}

#endif