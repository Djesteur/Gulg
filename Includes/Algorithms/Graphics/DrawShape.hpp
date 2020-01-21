#ifndef DRAW_SHAPE_HPP
#define DRAW_SHAPE_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/Shapes.hpp"

namespace Gg {

namespace Algorithm {

class DrawShape: public SpecializedAlgorithm {

	public:

		DrawShape(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							GulgEngine &gulgEngine);
		
		virtual ~DrawShape(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}}

#endif