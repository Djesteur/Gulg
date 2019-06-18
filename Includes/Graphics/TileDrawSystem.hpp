#ifndef TILE_DRAW_SYSTEM_HPP
#define TILE_DRAW_SYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "System.hpp"

#include "Graphics/DrawSpriteAlgorithm.hpp"
#include "Graphics/DrawVertexArrayAlgorithm.hpp"

namespace Gg {

class TileDrawSystem: public System {

	public:

		TileDrawSystem(sf::RenderTarget &renderTarget, EntitySignatureKeeper &entitySignatureKeeper, SignatureLoader &signatureLoader, 
					  ComponentKeeper &componentKeeper);
		
		virtual ~TileDrawSystem(); 

	protected:

};

}

#endif