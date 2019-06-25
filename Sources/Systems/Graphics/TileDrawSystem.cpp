#include "Systems/Graphics/TileDrawSystem.hpp"

TileDrawSystem::TileDrawSystem(sf::RenderTarget &m_renderTarget, Gg::GulgEngine &gulgEngine): System{gulgEngine} {


	m_algorithms.emplace_back(std::make_unique<Gg::DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileCenterVertex"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<Gg::DrawSpriteAlgorithm>(m_renderTarget, std::string{"TileConstructionSprite"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<Gg::DrawVertexArrayAlgorithm>(m_renderTarget, std::string{"TileBorderVertex"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<DrawSelectedTileBorderAlgorithm>(m_renderTarget, gulgEngine));
}

TileDrawSystem::~TileDrawSystem() {}
