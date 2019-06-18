#ifndef DRAW_SPRITE_ALGORITHM_HPP
#define DRAW_SPRITE_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/SpriteComponent.hpp"

namespace Gg {

class DrawSpriteAlgorithm: public SpecializedAlgorithm {

	public:

		DrawSpriteAlgorithm(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							GulgEngine &gulgEngine);
		
		virtual ~DrawSpriteAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}

#endif