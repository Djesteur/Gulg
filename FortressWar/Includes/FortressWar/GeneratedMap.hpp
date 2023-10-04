#ifndef GENERATED_MAP_HPP
#define GENERATED_MAP_HPP

#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include <SFML/Graphics/Rect.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

enum class TileType {

	NotDefined,
	Grass,
	Water,
	Earth,
	Sand,
	Stone
};

struct Tile {

	TileType type{TileType::NotDefined};
	std::string typeTexturePath{"GulgGraphics/Datas/DefaultTile.png"};

	unsigned int tilePositionX{0};
	unsigned int tilePositionY{0};
};

struct RiverSegment {

	glm::vec2 begin;
	glm::vec2 end;
};

struct GenerationDatas {

	unsigned int mapSizeX{0};
	unsigned int mapSizeY{0};

	//Grass and earth generation

	unsigned int numberOfGrassSeeds{0};
	unsigned int numberOfEarthSeeds{0};

	//River generation

	unsigned int numberOfRivers{0};
	float segmentSize{0};
	float riverWidth{0};


	//Road generation

	unsigned int numberOfRoads{0};
};

size_t getTileIndex(const size_t x, const size_t y, const size_t sizeX);
std::vector<size_t> getNeighbourgs4(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY);
std::vector<size_t> getNeighbourgs8(const std::vector<Tile> &map, const size_t center, const size_t mapSizeX, const size_t mapSizeY);
std::string getTexturePathFromTileType(const TileType type);

void generateGround(std::vector<Tile> &generatedMap, const GenerationDatas &datas);
void generateRivers(std::vector<Tile> &generatedMap, const GenerationDatas &datas);
void addSand(std::vector<Tile> &generatedMap, const GenerationDatas &datas);
void addStoneRoad(std::vector<Tile> &generatedMap, const GenerationDatas &datas);

std::vector<Tile> generateMap(const GenerationDatas &datas);

glm::vec2 projectionOnSegment(const glm::vec2 &segmentBegin, const glm::vec2 &segmentEnd, const glm::vec2 &point);
float norm(const glm::vec2 &vectorToNorm);
void applyRiverPathOnMap(const std::vector<RiverSegment> path, const float segmentWidth, std::vector<Tile> &generatedMap);

#endif