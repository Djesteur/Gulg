#include "Graphics/GraphicSystem.hpp"

namespace Gg {

GraphicSystem::GraphicSystem(sf::RenderTarget &m_renderTarget,
							 EntitySignatureKeeper &entitySignatureKeeper, 
							 SignatureLoader &signatureLoader,
							 ComponentKeeper &componentKeeper): System{entitySignatureKeeper, signatureLoader, componentKeeper} {


	m_algorithms.emplace_back(std::make_unique<DrawSpriteAlgorithm>(m_renderTarget, std::string{"MainSprite"}, componentKeeper, signatureLoader));
}

GraphicSystem::~GraphicSystem() {}


}