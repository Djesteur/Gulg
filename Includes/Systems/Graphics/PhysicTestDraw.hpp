#ifndef PYSIC_TEST_DRAW_HPP
#define PYSIC_TEST_DRAW_HPP

#include <SFML/Graphics.hpp>

#include "Systems/AbstractSystem.hpp"
#include "Algorithms/Graphics/DrawShape.hpp"

class PhysicTestDraw: public Gg::Systems::AbstractSystem {

	public:

		PhysicTestDraw(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~PhysicTestDraw(); 

};


#endif