#ifndef TILE_DRAW_SYSTEM_HPP
#define TILE_DRAW_SYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "Systems/System.hpp"

#include "Algorithms/Graphics/DrawSpriteAlgorithm.hpp"
#include "Algorithms/Graphics/DrawVertexArrayAlgorithm.hpp"

namespace Gg {

class TileDrawSystem: public System {

	public:

		TileDrawSystem(sf::RenderTarget &renderTarget, GulgEngine &gulgEngine);
		
		virtual ~TileDrawSystem(); 

	protected:

};

}

#endif