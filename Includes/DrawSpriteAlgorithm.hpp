#ifndef DRAW_SPRITE_ALGORITHM_HPP
#define DRAW_SPRITE_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "SpecializedAlgorithm.hpp"
#include "Graphics/SpriteComponent.hpp"

namespace Gg {

class DrawSpriteAlgorithm: public SpecializedAlgorithm {

	public:

		DrawSpriteAlgorithm(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							ComponentKeeper &componentKeeper, 
							SignatureLoader &signatureLoader);
		
		virtual ~DrawSpriteAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}

#endif