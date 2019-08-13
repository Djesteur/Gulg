#ifndef DRAW_VERTEX_ARRAY_HPP
#define DRAW_VERTEX_ARRAY_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/VertexArray.hpp"

namespace Gg {

namespace Algorithm {

class DrawVertexArray: public SpecializedAlgorithm {

	public:

		DrawVertexArray(sf::RenderTarget &renderTarget, 
								 const std::string componentName,
								 GulgEngine &gulgEngine);
		
		virtual ~DrawVertexArray(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}}

#endif