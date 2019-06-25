#ifndef  MAP_CONSTRUCTION_HPP
#define  MAP_CONSTRUCTION_HPP

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgDeclarations.hpp"
#include "GulgEngine/GulgEngine.hpp"

#include "Components/Graphics/VertexArrayComponent.hpp"
#include "Components/Game/HexaPosition.hpp"
#include "Components/BasicComponents.hpp"

#define PI 3.141592

std::vector<Gg::Entity> constructMap(const unsigned int hexaPixelSize,
						 	 		 const unsigned int sizeX,
							 		 const unsigned int sizeY,
						 	 		 Gg::GulgEngine &engine);

#endif