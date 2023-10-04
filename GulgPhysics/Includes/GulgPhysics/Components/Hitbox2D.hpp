#ifndef HITBOX_2D_COMPONENT_HPP
#define HITBOX_2D_COMPONENT_HPP

#include <vector>

#include "GulgECS/AbstractComponent.hpp"

namespace Gg {


struct Shape2D {

	std::vector<sf::Vector2f> vertices;
}

struct OBB: Shape2D {

	std::vector<glm::vec2> vertices;
}

struct Circle: Shape2D {

	float center;
	float radius;
}

namespace Component {

/**
 * @brief      This class describes a 2D hitbox component.
 */
class Hitbox2D: public AbstractComponent {

	public:


		/**
		 * @brief      Constructs a new instance.
		 */
		Hitbox2D();

		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param[in]  vertexShift     The shift between of the first vertice and the position of the object
		 * @param[in]  convexShapes  A shapes
		 * @param[in]  testConvexity Test the convexity of the shape. If it is not convex, divide it into convex shapes
		 */
		Hitbox2D(const sf::Vector2f &vertexShift, const Gg::Shape2D &convexShape, const testConvexity = true);

		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param[in]  vertexShift     The shift between of the first vertice and the position of the object
		 * @param[in]  convexShapes  A vector of shapes
		 * @param[in]  testConvexity Test the convexity of each shape. If a shape is not convex, divide it into convex shapes
		 */
		Hitbox2D(const sf::Vector2f &vertexShift, const std::vector<Gg::Shape2D> &convexShapes, const testConvexity = true);

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */
		virtual std::shared_ptr<AbstractComponent> clone() const;

		bool isInside(const sf::Vector2f &hitboxPosition, const sf::Vector2f &pointToTest) const;

		STATIC_GET_TYPE(Hitbox2D)

	private:

		sf::Vector2f m_vertexShift;
		std::vector<Shape2D> m_shapes;
           
};

}

}

#endif