#include "Game/MapConstruction.hpp"

void constructHexaCenter(std::shared_ptr<Gg::VertexArrayComponent> component,
						 const unsigned int hexaPixelSize,
						 const unsigned int positionX,
						 const unsigned int positionY) {


	component->vertexArray = sf::VertexArray{sf::TriangleFan, 8};

	component->vertexArray[0].position = sf::Vector2f{0.f, 0.f};
	component->vertexArray[1].position = sf::Vector2f{0.f, -static_cast<float>(hexaPixelSize)};
	component->vertexArray[7].position = component->vertexArray[1].position;

	const float angle{60.f*PI/180.f};
	float currentAngle{angle};

	for(unsigned int i{2}; i < 7; i++) {

		component->vertexArray[i].position.x = component->vertexArray[1].position.x*cos(currentAngle) + component->vertexArray[1].position.y*sin(currentAngle);
		component->vertexArray[i].position.y = -component->vertexArray[1].position.x*sin(currentAngle) + component->vertexArray[1].position.y*cos(currentAngle);
		currentAngle += angle;
	}

	for(size_t i{0}; i < component->vertexArray.getVertexCount(); i++) { 

		component->vertexArray[i].position += sf::Vector2f{static_cast<float>(positionX), static_cast<float>(positionY)};
	}
}

void constructHexaBorders(std::shared_ptr<Gg::VertexArrayComponent> component,
						 const unsigned int hexaPixelSize,
						 const unsigned int positionX,
						 const unsigned int positionY,
						 const int outerLimit,
						 const int innerLimit) {

	sf::VertexArray tempVertex{sf::LineStrip, 14};

	tempVertex[0].position = sf::Vector2f{0.f, -static_cast<float>(hexaPixelSize + outerLimit)};
	tempVertex[6].position = tempVertex[0].position;

	const float angle{60.f*PI/180.f};
	float currentAngle{angle};

	for(unsigned int i{1}; i < 6; i++) {

		tempVertex[i].position.x = tempVertex[0].position.x*cos(currentAngle) + tempVertex[0].position.y*sin(currentAngle);
		tempVertex[i].position.y = -tempVertex[0].position.x*sin(currentAngle) + tempVertex[0].position.y*cos(currentAngle);
		currentAngle += angle;
	}

	tempVertex[7].position = sf::Vector2f{0.f, -static_cast<float>(hexaPixelSize + innerLimit)};
	tempVertex[13].position = tempVertex[7].position;

	currentAngle = angle;

	for(unsigned int i{8}; i < 13; i++) {

		tempVertex[i].position.x = tempVertex[7].position.x*cos(currentAngle) + tempVertex[7].position.y*sin(currentAngle);
		tempVertex[i].position.y = -tempVertex[7].position.x*sin(currentAngle) + tempVertex[7].position.y*cos(currentAngle);
		currentAngle += angle;
	}

	for(size_t i{0}; i < tempVertex.getVertexCount(); i++) { 

		tempVertex[i].position += sf::Vector2f{static_cast<float>(positionX), static_cast<float>(positionY)};
	}

	component->vertexArray = sf::VertexArray{sf::Quads, 24};

	component->vertexArray[0] = tempVertex[0];
	component->vertexArray[1] = tempVertex[1];
	component->vertexArray[2] = tempVertex[8];
	component->vertexArray[3] = tempVertex[7];

	component->vertexArray[4] = tempVertex[1];
	component->vertexArray[5] = tempVertex[2];
	component->vertexArray[6] = tempVertex[9];
	component->vertexArray[7] = tempVertex[8];

	component->vertexArray[8] = tempVertex[2];
	component->vertexArray[9] = tempVertex[3];
	component->vertexArray[10] = tempVertex[10];
	component->vertexArray[11] = tempVertex[9];

	component->vertexArray[12] = tempVertex[3];
	component->vertexArray[13] = tempVertex[4];
	component->vertexArray[14] = tempVertex[11];
	component->vertexArray[15] = tempVertex[10];

	component->vertexArray[16] = tempVertex[4];
	component->vertexArray[17] = tempVertex[5];
	component->vertexArray[18] = tempVertex[12];
	component->vertexArray[19] = tempVertex[11];

	component->vertexArray[20] = tempVertex[5];
	component->vertexArray[21] = tempVertex[6];
	component->vertexArray[22] = tempVertex[13];
	component->vertexArray[23] = tempVertex[12];

}

void constructGraphicTile(Gg::Entity tile,
							 const unsigned int hexaPixelSize,
						 	 const unsigned int positionX,
						 	 const unsigned int positionY,
						 	 Gg::GulgEngine &engine) {

	std::shared_ptr<Gg::VertexArrayComponent> centerArray{std::make_shared<Gg::VertexArrayComponent>()};

	const float spacing{sqrtf(hexaPixelSize*hexaPixelSize*3.f/4.f)},
				xDistance{2.f*spacing},
				xBegin{spacing*(positionY%2)},
				yDistance{sqrtf(3.f*spacing*spacing)};

	constructHexaCenter(centerArray, hexaPixelSize, xBegin + positionX*xDistance, positionY*yDistance);

	for(size_t i{0}; i < centerArray->vertexArray.getVertexCount(); i++) {  centerArray->vertexArray[i].color = sf::Color::White; }

	engine.addComponentToEntity(tile, std::string{"TileCenterVertex"}, std::static_pointer_cast<Gg::Component>(centerArray));

	std::shared_ptr<Gg::VertexArrayComponent> borderArray{std::make_shared<Gg::VertexArrayComponent>()};

	constructHexaBorders(borderArray, hexaPixelSize, xBegin + positionX*xDistance, positionY*yDistance, 1, -9);
	for(size_t i{0}; i < borderArray->vertexArray.getVertexCount(); i++) {  borderArray->vertexArray[i].color = sf::Color{48, 162, 190}; }

	engine.addComponentToEntity(tile, std::string{"TileBorderVertex"}, std::static_pointer_cast<Gg::Component>(borderArray));

	
	std::shared_ptr<Gg::VertexArrayComponent> selectedBorderArray{std::make_shared<Gg::VertexArrayComponent>()};

	constructHexaBorders(selectedBorderArray, hexaPixelSize, xBegin + positionX*xDistance, positionY*yDistance, 1, -29);
	for(size_t i{0}; i < selectedBorderArray->vertexArray.getVertexCount(); i++) {  selectedBorderArray->vertexArray[i].color = sf::Color{76, 187, 23}; }

	engine.addComponentToEntity(tile, std::string{"TileSelectedBorderVertex"}, std::static_pointer_cast<Gg::Component>(selectedBorderArray));


	std::shared_ptr<Gg::BooleanComponent> isSelectedBorderArray{std::make_shared<Gg::BooleanComponent>()};
	isSelectedBorderArray->value = false;
	engine.addComponentToEntity(tile, std::string{"IsTileSelectedBorderVertex"}, std::static_pointer_cast<Gg::Component>(isSelectedBorderArray));
}

void constructPositionTile(Gg::Entity tile, 
						   const unsigned int x, 
						   const unsigned int y, 
						   Gg::GulgEngine &engine) {

	std::shared_ptr<Gg::HexaPosition> hexaPos{std::make_shared<Gg::HexaPosition>(x, y)};
	engine.addComponentToEntity(tile, std::string{"TileHexaPosition"}, std::static_pointer_cast<Gg::Component>(hexaPos));
}

std::vector<Gg::Entity> constructMap(const unsigned int hexaPixelSize,
						 	 		 const unsigned int sizeX,
							 		 const unsigned int sizeY,
						 	 		 Gg::GulgEngine &engine) {

	std::vector<Gg::Entity> map;
	map.reserve(sizeX*sizeY);

	Gg::Entity newTile;

	for(unsigned int x{0}; x < sizeX; x++) {
		for(unsigned int y{0}; y < sizeY; y++) {

			newTile = engine.getNewEntity();
			map.emplace_back(newTile);

			constructGraphicTile(newTile, hexaPixelSize, x, y, engine);
			constructPositionTile(newTile, x, y, engine);
		}
	}

	return map;
}