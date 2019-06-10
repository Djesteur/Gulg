#ifndef SPRITE_ALGORITHM_HPP
#define SPRITE_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "Algorithm.hpp"
#include "Graphics/SpriteComponent.hpp"

namespace Gg {

class SpriteAlgorithm: public Algorithm {

	public:

		SpriteAlgorithm(sf::RenderTarget &renderTarget, SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper);
		virtual ~SpriteAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}

#endif