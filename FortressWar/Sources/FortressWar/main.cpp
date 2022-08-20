#include <SFML/System/Vector2.hpp>

#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

#include "GulgGraphics/Systems/Graphics2D.hpp"
#include "GulgGraphics/Components/Sprite.hpp"

#include "GulgInput/Event.hpp"
#include "GulgInput/Action.hpp"
#include "GulgInput/InputUpdater.hpp"

#include "FortressWar/GeneratedMap.hpp"

void inputTestFunction() { std::cout << "Z has been pressed !" << std::endl; }

int main() {

	const sf::Vector2u mapSize{100, 100};
	const sf::Vector2u tileTextureSize{32, 32};
	const sf::VideoMode windowVideoMode{800, 800};

	GenerationDatas datas;

	datas.mapSizeX = mapSize.x;
	datas.mapSizeY = mapSize.y;
	datas.numberOfGrassSeeds = 12;
	datas.numberOfEarthSeeds = 4;
	datas.numberOfRivers = 1;
	datas.segmentSize = 3.f;
	datas.riverWidth = 2.f;
	datas.numberOfRoads = 0;

	std::vector<Tile> tileMap = generateMap(datas);

	Gg::GulgEngine engine;

	sf::RenderWindow window{windowVideoMode, "Gulg Graphics"};

	std::shared_ptr<Gg::System::Graphics2D> graphicSystem = engine.createSystem<Gg::System::Graphics2D>(window);

	for(Tile &currentTile: tileMap) {

		Gg::Entity currentTileEntity{engine.createEntity()};
		engine.createComponent<Gg::Component::Sprite>(currentTileEntity, sf::Vector2f{currentTile.tilePositionX*tileTextureSize.x*1.f, currentTile.tilePositionY*tileTextureSize.y*1.f}, currentTile.typeTexturePath);
		engine.addEntityToSystem<Gg::System::Graphics2D>(currentTileEntity);
	}

	sf::View tileMapView;
	tileMapView.setCenter(mapSize.x*tileTextureSize.x/2, mapSize.y*tileTextureSize.y/2);
	tileMapView.setSize(mapSize.x*tileTextureSize.x, mapSize.y*tileTextureSize.y);
	tileMapView.setViewport(sf::FloatRect{0.f, 0.f, 1.f, 1.f});

	window.setView(tileMapView);

	Gg::Input::InputUpdater updater;
	updater.createActionGroup("MainGroup");
	std::shared_ptr<Gg::Input::Action> testAction{updater.createAction("MainGroup")};

	testAction->addEvent(Gg::Input::Event{Gg::Input::HandledInput::Z, Gg::Input::EventType::ButtonPressed});
	testAction->addCallback(std::function<void()>{inputTestFunction});

	while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))  {

        	switch (event.type) {

        		case sf::Event::Closed:
        			window.close();
        			break;

        		case sf::Event::KeyPressed:
        			updater.update();
        			break;
        	}
        }

        graphicSystem->update(0);
    }


	return 0;
}