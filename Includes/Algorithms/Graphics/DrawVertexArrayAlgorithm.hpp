#ifndef DRAW_VERTEX_ARRAY_ALGORITHM_HPP
#define DRAW_VERTEX_ARRAY_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/VertexArrayComponent.hpp"

namespace Gg {

class DrawVertexArrayAlgorithm: public SpecializedAlgorithm {

	public:

		DrawVertexArrayAlgorithm(sf::RenderTarget &renderTarget, 
								 const std::string componentName,
								 GulgEngine &gulgEngine);
		
		virtual ~DrawVertexArrayAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}

#endif