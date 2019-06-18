#include "Graphics/TileDrawSystem.hpp"

namespace Gg {

TileDrawSystem::TileDrawSystem(sf::RenderTarget &m_renderTarget,
							 EntitySignatureKeeper &entitySignatureKeeper, 
							 SignatureLoader &signatureLoader,
							 ComponentKeeper &componentKeeper): System{entitySignatureKeeper, signatureLoader, componentKeeper} {


	m_algorithms.emplace_back(std::make_unique<DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileCenterVertex"}, componentKeeper, signatureLoader));
	m_algorithms.emplace_back(std::make_unique<DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileBorderVertex"}, componentKeeper, signatureLoader));
	m_algorithms.emplace_back(std::make_unique<DrawSpriteAlgorithm>(m_renderTarget, std::string{"TileConstructionSprite"}, componentKeeper, signatureLoader));
}

TileDrawSystem::~TileDrawSystem() {}


}