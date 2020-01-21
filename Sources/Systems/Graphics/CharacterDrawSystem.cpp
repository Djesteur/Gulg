#include "Systems/Graphics/CharacterDraw.hpp"

CharacterDraw::CharacterDraw(sf::RenderTarget &m_renderTarget, Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::DrawAnimationSet>(m_renderTarget, std::string{"Animation"}, gulgEngine));
	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::DrawShape>(m_renderTarget, std::string{"GraphicHitbox"}, gulgEngine));
}

CharacterDraw::~CharacterDraw() {}
