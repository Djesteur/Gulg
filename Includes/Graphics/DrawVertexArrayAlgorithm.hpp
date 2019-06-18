#ifndef DRAW_VERTEX_ARRAY_ALGORITHM_HPP
#define DRAW_VERTEX_ARRAY_ALGORITHM_HPP

#include <SFML/Graphics.hpp>

#include "SpecializedAlgorithm.hpp"
#include "Graphics/VertexArrayComponent.hpp"

namespace Gg {

class DrawVertexArrayAlgorithm: public SpecializedAlgorithm {

	public:

		DrawVertexArrayAlgorithm(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							ComponentKeeper &componentKeeper, 
							SignatureLoader &signatureLoader);
		
		virtual ~DrawVertexArrayAlgorithm(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}

#endif