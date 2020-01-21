#ifndef DRAW_ANIMATION_SET_HPP
#define DRAW_ANIMATION_SET_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/SpecializedAlgorithm.hpp"
#include "Components/Graphics/AnimationSet.hpp"

namespace Gg {

namespace Algorithm {

class DrawAnimationSet: public SpecializedAlgorithm {

	public:

		DrawAnimationSet(sf::RenderTarget &renderTarget, 
						 const std::string componentName, 
						 GulgEngine &gulgEngine);
		
		virtual ~DrawAnimationSet(); 

		void apply(); 

	protected:

		sf::RenderTarget &m_renderTarget;    
};

}}

#endif