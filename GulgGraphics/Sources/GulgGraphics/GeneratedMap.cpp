#include "GeneratedMap.hpp"

size_t getTileIndex(const size_t x, const size_t y, const size_t sizeX) { return sizeX*y+ x; }

std::vector<size_t> getNeighbourgs4(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY) {

	const unsigned int positionX = map[center].tilePositionX;
	const unsigned int positionY = map[center].tilePositionY;

	std::vector<size_t> neighbourgs;

	if(positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX, positionY - 1, mapSizeX)); }
	if(positionX != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY, mapSizeX)); }
	if(positionX != mapSizeX - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY, mapSizeX)); }
	if(positionY != mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX, positionY + 1, mapSizeX)); }

	return neighbourgs;
}

std::vector<size_t> getNeighbourgs8(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY) {

	const unsigned int positionX = map[center].tilePositionX;
	const unsigned int positionY = map[center].tilePositionY;

	std::vector<size_t> neighbourgs;

	if(positionX != 0 && positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY - 1, mapSizeX)); }
	if(positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX, positionY - 1, mapSizeX)); }
	if(positionX != mapSizeX - 1 && positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY - 1, mapSizeX)); }
	if(positionX != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY, mapSizeX)); }
	if(positionX != mapSizeX - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY, mapSizeX)); }
	if(positionX != 0 && positionY != mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY + 1, mapSizeX)); }
	if(positionY != mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX, positionY + 1, mapSizeX)); }
	if(positionX != mapSizeX - 1 && positionY != mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY + 1, mapSizeX)); }

	return neighbourgs;
}

std::string getTexturePathFromTileType(const TileType type) {

	switch(type) {

		case TileType::Grass:
			return "GulgGraphics/Datas/Grass.png";
			break;

		case TileType::Water:
			return "GulgGraphics/Datas/Water.png";
			break;

		case TileType::Earth:
			return "GulgGraphics/Datas/Earth.png";
			break;

		case TileType::Sand:
			return "GulgGraphics/Datas/Sand.png";
			break;

		case TileType::Stone:
			return "GulgGraphics/Datas/Stone.png";
			break;

		case TileType::NotDefined:
			return "GulgGraphics/Datas/DefaultTile.png";
			break;
	}

	return "GulgGraphics/Datas/DefaultTile.png";
}

void generateGround(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

	std::vector<size_t> openGrassList, closedGrassList, addToOpenGrassList, addToCloseGrassList;
	std::vector<size_t> openEarthList, closedEarthList, addToOpenEarthList, addToCloseEarthList;

	std::default_random_engine engine { std::time(nullptr) };
    std::uniform_int_distribution<unsigned int> distribution(0, generatedMap.size() - 1);

    for(unsigned int i{0}; i < datas.numberOfGrassSeeds; i++) {

    	size_t randomSeed{distribution(engine)};

    	if(std::find(openGrassList.begin(), openGrassList.end(), randomSeed) != openGrassList.end()) { i--; }
    	else { openGrassList.emplace_back(randomSeed); }
    }

    for(unsigned int i{0}; i < datas.numberOfEarthSeeds; i++) {

    	size_t randomSeed{distribution(engine)};

    	if(std::find(openGrassList.begin(), openGrassList.end(), randomSeed) != openGrassList.end()
    	&& std::find(openEarthList.begin(), openEarthList.end(), randomSeed) != openEarthList.end() ) { i--; }

    	else { openEarthList.emplace_back(randomSeed); }
    }

    for(size_t currentGrass: openGrassList) { generatedMap[currentGrass].type = TileType::Grass; }
    for(size_t currentEarth: openEarthList) { generatedMap[currentEarth].type = TileType::Earth; }

    while(!openGrassList.empty() || !openEarthList.empty()) {

    	addToOpenGrassList.clear();
    	addToOpenEarthList.clear();

	    for(size_t currentGrass: openGrassList) {

	    	std::vector<size_t> neighbourgs = getNeighbourgs4(generatedMap, currentGrass, datas.mapSizeX, datas.mapSizeX);

	    	for(size_t currentNeighbourgs: neighbourgs) {

	    		if(generatedMap[currentNeighbourgs].type == TileType::NotDefined) {

	    			generatedMap[currentNeighbourgs].type = TileType::Grass;
	    			addToOpenGrassList.emplace_back(currentNeighbourgs);
	    		}
	    	}
	    }

	    for(size_t currentEarth: openEarthList) {

	    	std::vector<size_t> neighbourgs = getNeighbourgs4(generatedMap, currentEarth, datas.mapSizeX, datas.mapSizeX);

	    	for(size_t currentNeighbourgs: neighbourgs) {

	    		if(generatedMap[currentNeighbourgs].type == TileType::NotDefined) {

	    			generatedMap[currentNeighbourgs].type = TileType::Earth;
	    			addToOpenEarthList.emplace_back(currentNeighbourgs);
	    		}
	    	}
	    }

	    openGrassList = addToOpenGrassList;
	    openEarthList = addToOpenEarthList;
	}

}

/*sf::Vector2f normalize(sf::Vector2f vector) {

	if(vector.x == 0.f && vector.x == 0.f) { return vector; }
	return vector/sqrt(vector.x*vector.x + vector.y*vector.y)
}*/

void generateRivers(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

	//Todo: make it random

	/*const sf::Vector2f beginRiver{-1, datas.mapSizeY/2};
	const sf::Vector2f endRiver{datas.mapSizeX, datas.mapSizeY/2};

	const sf::Vector2f angleConstraint1{0.f, 1.f}, angleConstraint2{0.f, -1.f};

	//End random

	const float maxAngle{90.f};
	const unsigned int tilePerSegment{3};

	sf::Vector2f previousDirection{normalize(endRiver - beginRiver)};

	sf::Vector2f beginCurrentSegment{beginRiverX, beginRiverY};

	const float sinAngle1{sin(maxAngle/2)};
	const float cosAngle1{cos(maxAngle/2)};

	sf::Vector2f nextSegment{]nextSegmentBorder1, nextSegmentBorder2;
	nextSegmentBorder1.x = beginCurrentSegment*cosAngle1 + */




}

void addSand(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

}

void addStoneRoad(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

}



std::vector<Tile> generateMap(const GenerationDatas &datas) {

	std::vector<Tile> generatedMap{datas.mapSizeX*datas.mapSizeY};


	if(datas.numberOfGrassSeeds + datas.numberOfEarthSeeds > datas.mapSizeX*datas.mapSizeY) { return generatedMap;}


	for(size_t i{0}; i < datas.mapSizeX; i++) {
		for(size_t j{0}; j < datas.mapSizeY; j++) {

			size_t tileIndex = getTileIndex(i, j, datas.mapSizeX);

			generatedMap[tileIndex].tilePositionX = i;
			generatedMap[tileIndex].tilePositionY = j;
		}
	}

	generateGround(generatedMap, datas);
	generateRivers(generatedMap, datas);
	addSand(generatedMap, datas);
	addStoneRoad(generatedMap, datas);

	for(size_t i{0}; i < datas.mapSizeX; i++) {
		for(size_t j{0}; j < datas.mapSizeY; j++) {

			size_t tileIndex = getTileIndex(i, j, datas.mapSizeX);

			generatedMap[tileIndex].typeTexturePath = getTexturePathFromTileType(generatedMap[tileIndex].type);
		}
	}

	return generatedMap;
}