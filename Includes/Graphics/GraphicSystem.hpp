#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "System.hpp"
#include "Graphics/SpriteAlgorithm.hpp"

namespace Gg {

class GraphicSystem: public System {

	public:

		GraphicSystem(sf::RenderTarget &renderTarget, EntitySignatureKeeper &entitySignatureKeeper, SignatureLoader &signatureLoader, 
					  ComponentKeeper &componentKeeper);
		virtual ~GraphicSystem(); 

	protected:

};

}

#endif