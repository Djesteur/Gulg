#ifndef PYSIC_TEST_CIRCLE_DRAW_HPP
#define PYSIC_TEST_CIRCLE_DRAW_HPP

#include <SFML/Graphics.hpp>

#include "Systems/AbstractSystem.hpp"
#include "Algorithms/Graphics/DrawCircleShape.hpp"

class PhysicTestDrawCircle: public Gg::Systems::AbstractSystem {

	public:

		PhysicTestDrawCircle(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~PhysicTestDrawCircle(); 

	protected:

};


#endif