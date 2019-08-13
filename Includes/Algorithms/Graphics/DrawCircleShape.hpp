#ifndef DRAW_CIRCLE_SHAPE_HPP
#define DRAW_CIRCLE_SHAPE_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/CircleShape.hpp"

namespace Gg {

namespace Algorithm {

class DrawCircleShape: public SpecializedAlgorithm {

	public:

		DrawCircleShape(sf::RenderTarget &renderTarget, 
							const std::string componentName, 
							GulgEngine &gulgEngine);
		
		virtual ~DrawCircleShape(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}}

#endif