#ifndef TILE_DRAW_SYSTEM_HPP
#define TILE_DRAW_SYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "Systems/System.hpp"

#include "Algorithms/Graphics/DrawSpriteAlgorithm.hpp"
#include "Algorithms/Graphics/DrawVertexArrayAlgorithm.hpp"
#include "Algorithms/Graphics/DrawSelectedTileBorderAlgorithm.hpp"

class TileDrawSystem: public Gg::System {

	public:

		TileDrawSystem(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~TileDrawSystem(); 

	protected:

};


#endif