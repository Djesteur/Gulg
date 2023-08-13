#include "FortressWar/GeneratedMap.hpp"

size_t getTileIndex(const size_t x, const size_t y, const size_t sizeX) { return sizeX*y+ x; }

std::vector<size_t> getNeighbourgs4(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY) {

	const unsigned int positionX = map[center].tilePositionX;
	const unsigned int positionY = map[center].tilePositionY;

	std::vector<size_t> neighbourgs;

	if(positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX, positionY - 1, mapSizeX)); }
	if(positionX != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY, mapSizeX)); }
	if(positionX < mapSizeX - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY, mapSizeX)); }
	if(positionY < mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX, positionY + 1, mapSizeX)); }

	return neighbourgs;
}

std::vector<size_t> getNeighbourgs8(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY) {

	const unsigned int positionX = map[center].tilePositionX;
	const unsigned int positionY = map[center].tilePositionY;

	std::vector<size_t> neighbourgs;

	if(positionX != 0 && positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY - 1, mapSizeX)); }
	if(positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX, positionY - 1, mapSizeX)); }
	if(positionX < mapSizeX - 1 && positionY != 0) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY - 1, mapSizeX)); }
	if(positionX != 0) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY, mapSizeX)); }
	if(positionX < mapSizeX - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY, mapSizeX)); }
	if(positionX != 0 && positionY < mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX - 1, positionY + 1, mapSizeX)); }
	if(positionY < mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX, positionY + 1, mapSizeX)); }
	if(positionX < mapSizeX - 1 && positionY < mapSizeY - 1) { neighbourgs.emplace_back(getTileIndex(positionX + 1, positionY + 1, mapSizeX)); }

	return neighbourgs;
}

std::string getTexturePathFromTileType(const TileType type) {

	switch(type) {

		case TileType::Grass:
			return "FortressWar/Datas/Grass.png";
			break;

		case TileType::Water:
			return "FortressWar/Datas/Water.png";
			break;

		case TileType::Earth:
			return "FortressWar/Datas/Earth.png";
			break;

		case TileType::Sand:
			return "FortressWar/Datas/Sand.png";
			break;

		case TileType::Stone:
			return "FortressWar/Datas/Stone.png";
			break;

		case TileType::NotDefined:
			return "FortressWar/Datas/DefaultTile.png";
			break;
	}

	return "FortressWar/Datas/DefaultTile.png";
}

void generateGround(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

	std::vector<size_t> openGrassList, closedGrassList, addToOpenGrassList, addToCloseGrassList;
	std::vector<size_t> openEarthList, closedEarthList, addToOpenEarthList, addToCloseEarthList;

	std::default_random_engine engine { std::chrono::system_clock::now().time_since_epoch().count() };
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

	    	std::vector<size_t> neighbourgs = getNeighbourgs8(generatedMap, currentGrass, datas.mapSizeX, datas.mapSizeY);

	    	for(size_t currentNeighbourgs: neighbourgs) {

	    		if(generatedMap[currentNeighbourgs].type == TileType::NotDefined) {

	    			generatedMap[currentNeighbourgs].type = TileType::Grass;
	    			addToOpenGrassList.emplace_back(currentNeighbourgs);
	    		}
	    	}
	    }

	    for(size_t currentEarth: openEarthList) {

	    	std::vector<size_t> neighbourgs = getNeighbourgs8(generatedMap, currentEarth, datas.mapSizeX, datas.mapSizeY);

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

sf::Vector2f normalize(const sf::Vector2f &vector) {

	if(vector.x == 0.f && vector.x == 0.f) { return vector; }
	return vector/sqrtf(vector.x*vector.x + vector.y*vector.y);
}

sf::Vector2f rotateAround(const sf::Vector2f &pivot, const sf::Vector2f &pointToRotate, const float angle) {

	sf::Vector2f tmp{pointToRotate - pivot}, result{0.f, 0.f};
	result.x = tmp.x*cos(angle) - tmp.y*sin(angle);
	result.y = tmp.x*sin(angle) + tmp.y*cos(angle);

	return result + pivot;
}

std::vector<RiverSegment> generateRiverPath(const GenerationDatas &datas) {

	std::vector<RiverSegment> resultPath;

	std::default_random_engine engine { std::chrono::system_clock::now().time_since_epoch().count() };

	const unsigned int tilePerSegment{datas.segmentSize};

	//Todo: take from datas

	const float maxAngle{3.14159f/2.f};

	//Select the beginning point and the direction

	std::uniform_int_distribution<int> beginningSideDistribution(0, 3);
	const int choosenSide = beginningSideDistribution(engine);

	std::uniform_real_distribution<float> beginningPointDistribution(0.f, 1.f);
	const float choosenPoint = beginningPointDistribution(engine);

	sf::Vector2f previousDirection{0.f, 0.f};
	sf::Vector2f beginCurrentSegment{0.f, 0.f};

	if(choosenSide == 0) { beginCurrentSegment = sf::Vector2f{0.f, choosenPoint}; previousDirection = normalize(sf::Vector2f{1.f, 1.f - choosenPoint} - beginCurrentSegment); }
	if(choosenSide == 1) { beginCurrentSegment = sf::Vector2f{1.f, choosenPoint}; previousDirection = normalize(sf::Vector2f{0.f, 1.f - choosenPoint} - beginCurrentSegment); } 
	if(choosenSide == 2) { beginCurrentSegment = sf::Vector2f{choosenPoint, 0.f}; previousDirection = normalize(sf::Vector2f{1.f - choosenPoint, 1.f} - beginCurrentSegment); } 
	if(choosenSide == 3) { beginCurrentSegment = sf::Vector2f{choosenPoint, 1.f}; previousDirection = normalize(sf::Vector2f{1.f - choosenPoint, 0.f} - beginCurrentSegment); }


	beginCurrentSegment.x *= datas.mapSizeX;
	beginCurrentSegment.y *= datas.mapSizeY;

	//End random

	bool haveToContinue{true};


	while(haveToContinue) {

		sf::Vector2f endCurrentSegment{beginCurrentSegment + previousDirection*static_cast<float>(tilePerSegment)};

		float segmentLeftAngle{-maxAngle/2.f}, segmentRightAngle{maxAngle/2.f};
		//Todo: constraint angles


		std::uniform_real_distribution<float> distribution(segmentLeftAngle, segmentRightAngle);
	    float testAngle = distribution(engine)/2.f;

	    sf::Vector2f beginNextSegment{rotateAround(beginCurrentSegment, endCurrentSegment, testAngle)};
		previousDirection = normalize(beginNextSegment - beginCurrentSegment);

		RiverSegment newSegment;
		newSegment.begin = beginCurrentSegment;
		newSegment.end = beginNextSegment;
		resultPath.emplace_back(newSegment);
		beginCurrentSegment = beginNextSegment;

		if(floor(beginCurrentSegment.x) < 0.f
		|| static_cast<size_t>(floor(beginCurrentSegment.x)) >= datas.mapSizeX
		|| floor(beginCurrentSegment.y) < 0.f
		|| static_cast<size_t>(floor(beginCurrentSegment.y)) >= datas.mapSizeY) { haveToContinue = false; }
	}

	return resultPath;
}

sf::Vector2f projectionOnSegment(const sf::Vector2f &segmentBegin, const sf::Vector2f &segmentEnd, const sf::Vector2f &point) {

	const sf::Vector2f beginToPoint{point - segmentBegin};
	const sf::Vector2f beginToEnd{segmentEnd - segmentBegin};

	const float dotAB{beginToPoint.x*beginToEnd.x + beginToPoint.y*beginToEnd.y};
	const float dotBB{beginToEnd.x*beginToEnd.x + beginToEnd.y*beginToEnd.y};

	return segmentBegin + (dotAB/(dotBB*dotBB))*beginToEnd;
}

float norm(const sf::Vector2f &vectorToNorm) { return sqrtf(vectorToNorm.x*vectorToNorm.x + vectorToNorm.y*vectorToNorm.y); }
 
void applyRiverPathOnMap(const std::vector<RiverSegment> path, const float segmentWidth, std::vector<Tile> &generatedMap) {

	for(Tile &currentTile: generatedMap) {

		const sf::Vector2f tileCenter{currentTile.tilePositionX + 0.5f, currentTile.tilePositionY + 0.5f};

		for(const RiverSegment &currentSegment: path) {

			const sf::Vector2f projection{projectionOnSegment(currentSegment.begin, currentSegment.end, tileCenter)};

			if(norm(tileCenter - projection) <= segmentWidth) { currentTile.type = TileType::Water; }
		}
	}
}

void generateRivers(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

	for(size_t nbRiver{0}; nbRiver < datas.numberOfRivers; nbRiver++) {

		applyRiverPathOnMap(generateRiverPath(datas), datas.riverWidth, generatedMap);
	}
}

void addSand(std::vector<Tile> &generatedMap, const GenerationDatas &datas) {

	for(size_t i{0}; i < generatedMap.size(); i++) {

		std::vector<size_t> neighbourgs = getNeighbourgs8(generatedMap, i, datas.mapSizeX, datas.mapSizeY);

		for(size_t currentNeighbourgs: neighbourgs) {

			if(generatedMap[currentNeighbourgs].type == TileType::Water && generatedMap[i].type != TileType::Water) { generatedMap[i].type = TileType::Sand; }
		}
	}
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