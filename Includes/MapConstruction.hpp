#ifndef  HEXA_CONSTRUCTION_HPP
#define  HEXA_CONSTRUCTION_HPP

#include <SFML/Graphics.hpp>

#include "GulgDeclarations.hpp"
#include "EntityCreator.hpp"
#include "EntitySignatureKeeper.hpp"
#include "SignatureLoader.hpp"
#include "ComponentKeeper.hpp"
#include "Component.hpp"

#include "Graphics/VertexArrayComponent.hpp"

#define PI 3.141592

Gg::Entity getNewEntity(Gg::EntityCreator &creator, 
						Gg::EntitySignatureKeeper &entitySignatureKeeper,
						Gg::ComponentKeeper &componentKeeper);

void addComponentToEntity(const Gg::Entity entity, const std::string name, std::shared_ptr<Gg::Component> component,
						  Gg::ComponentKeeper &componentKeeper, 
						  Gg::EntitySignatureKeeper &signatureKeeper,
						  Gg::SignatureLoader &loader);

Gg::Entity constructHexaTile(const unsigned int hexaPixelSize,
						 	 const unsigned int positionX,
							 const unsigned int positionY,
						 	 Gg::EntityCreator &creator, 
						 	 Gg::EntitySignatureKeeper &entitySignatureKeeper,
						 	 Gg::ComponentKeeper &componentKeeper,
						 	 Gg::SignatureLoader &loader);

#endif