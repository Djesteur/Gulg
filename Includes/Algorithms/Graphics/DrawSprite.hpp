#ifndef DRAW_SPRITE_HPP
#define DRAW_SPRITE_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/Sprite.hpp"

namespace Gg {

namespace Algorithm {

class DrawSprite: public SpecializedAlgorithm {

	public:

		DrawSprite(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							GulgEngine &gulgEngine);
		
		virtual ~DrawSprite(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}}

#endif