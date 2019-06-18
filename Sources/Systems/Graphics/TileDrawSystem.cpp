#include "Systems/Graphics/TileDrawSystem.hpp"

namespace Gg {

TileDrawSystem::TileDrawSystem(sf::RenderTarget &m_renderTarget, GulgEngine &gulgEngine): System{gulgEngine} {


	m_algorithms.emplace_back(std::make_unique<DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileCenterVertex"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileBorderVertex"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<DrawSpriteAlgorithm>(m_renderTarget, std::string{"TileConstructionSprite"}, gulgEngine));
}

TileDrawSystem::~TileDrawSystem() {}


}