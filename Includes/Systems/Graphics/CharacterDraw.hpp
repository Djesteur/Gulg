#ifndef CHARACTER_DRAW_HPP
#define CHARACTER_DRAW_HPP

#include <SFML/Graphics.hpp>

#include "Systems/AbstractSystem.hpp"
#include "Algorithms/Graphics/DrawAnimationSet.hpp"
#include "Algorithms/Graphics/DrawCircleShape.hpp"

class CharacterDraw: public Gg::Systems::AbstractSystem {

	public:

		CharacterDraw(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~CharacterDraw(); 

	protected:

};


#endif