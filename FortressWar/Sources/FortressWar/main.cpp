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

void testZPressed() { std::cout << "Z has been pressed  !" << std::endl; }
void testZStillPressed() { std::cout << "Z is still pressed  !" << std::endl; }
void testZReleased() { std::cout << "Z has been released !" << std::endl; }

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

	Gg::Input::InputUpdater inputUpdater{window};
	inputUpdater.createActionGroup("MainGroup");

	std::shared_ptr<Gg::Input::Action> testAction1{inputUpdater.createAction("MainGroup")};
	testAction1->addEvent(Gg::Input::Event{Gg::Input::HandledInput::Z, Gg::Input::EventType::ButtonPressed});
	testAction1->addCallback(std::function<void()>{testZPressed});

	std::shared_ptr<Gg::Input::Action> testAction2{inputUpdater.createAction("MainGroup")};
	testAction2->addEvent(Gg::Input::Event{Gg::Input::HandledInput::Z, Gg::Input::EventType::ButtonStillPressed});
	testAction2->addCallback(std::function<void()>{testZStillPressed});

	std::shared_ptr<Gg::Input::Action> testAction3{inputUpdater.createAction("MainGroup")};
	testAction3->addEvent(Gg::Input::Event{Gg::Input::HandledInput::Z, Gg::Input::EventType::ButtonReleased});
	testAction3->addCallback(std::function<void()>{testZReleased});

	while (window.isOpen()) {

		std::vector<Gg::Input::Event> notHandledByInputUpdater = inputUpdater.update();

		for(Gg::Input::Event currentEvent: notHandledByInputUpdater) {

			switch (currentEvent.eventType) {

        		case Gg::Input::EventType::WindowClosed:
        			window.close();
        			break;

        		default:
        			break;
        	}
		}

        graphicSystem->update(0);
    }


	return 0;
}