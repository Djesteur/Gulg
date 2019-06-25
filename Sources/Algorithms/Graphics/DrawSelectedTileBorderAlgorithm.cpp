#include "Algorithms/Graphics/DrawSelectedTileBorderAlgorithm.hpp"

DrawSelectedTileBorderAlgorithm::DrawSelectedTileBorderAlgorithm(sf::RenderTarget &renderTarget, Gg::GulgEngine &gulgEngine): 
	Algorithm{gulgEngine},
	m_renderTarget{renderTarget} {

	m_signature = gulgEngine.getComponentSignature("TileSelectedBorderVertex")
				+ gulgEngine.getComponentSignature("IsTileSelectedBorderVertex");
}

DrawSelectedTileBorderAlgorithm::~DrawSelectedTileBorderAlgorithm() {}

void DrawSelectedTileBorderAlgorithm::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Gg::BooleanComponent> isSelected{ 
			std::static_pointer_cast<Gg::BooleanComponent>(m_gulgEngine.getComponent(currentEntity, "IsTileSelectedBorderVertex"))
		};

		if(isSelected->value) {

			std::shared_ptr<Gg::VertexArrayComponent> borderToDraw{
				std::static_pointer_cast<Gg::VertexArrayComponent>(m_gulgEngine.getComponent(currentEntity, "TileSelectedBorderVertex"))
			};

			m_renderTarget.draw(borderToDraw->vertexArray);
		}
	}
}