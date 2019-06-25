#ifndef DRAW_SELECTED_TILE_BORDER_ALGORITHM_HPP
#define DRAW_SELECTED_TILE_BORDER_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/Algorithm.hpp"

#include "Components/Graphics/VertexArrayComponent.hpp"
#include "Components/BasicComponents.hpp"

class DrawSelectedTileBorderAlgorithm: public Gg::Algorithm {

	public:

		DrawSelectedTileBorderAlgorithm(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine);
		
		virtual ~DrawSelectedTileBorderAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

#endif