#ifndef  MAP_CONSTRUCTION_HPP
#define  MAP_CONSTRUCTION_HPP

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgDeclarations.hpp"
#include "GulgEngine/GulgEngine.hpp"

#include "Components/Graphics/VertexArrayComponent.hpp"

#define PI 3.141592

Gg::Entity constructHexaTile(const unsigned int hexaPixelSize,
						 	 const unsigned int positionX,
							 const unsigned int positionY,
						 	 Gg::GulgEngine &engine);

#endif