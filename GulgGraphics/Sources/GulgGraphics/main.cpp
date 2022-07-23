#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

#include "GulgGraphics/GraphicSystem.hpp"
#include "GulgGraphics/SpriteComponent.hpp"

#include <SFML/Graphics.hpp>

int main() {

	Gg::GulgEngine engine;


	sf::RenderWindow window{sf::VideoMode{800, 800}, "Gulg Graphics"};

	std::shared_ptr<Gg::System::GraphicSystem> graphicSystem = engine.createSystem<Gg::System::GraphicSystem>(window);

	Gg::Entity newEntity1{engine.createEntity()};
	engine.createComponent<Gg::Component::SpriteComponent>(newEntity1, sf::Vector2f{400.f, 200.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/White.png");
	engine.addEntityToSystem<Gg::System::GraphicSystem>(newEntity1);

	Gg::Entity newEntity2{engine.createEntity()};
	engine.createComponent<Gg::Component::SpriteComponent>(newEntity2, sf::Vector2f{650.f, 350.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Blue.png");
	engine.addEntityToSystem<Gg::System::GraphicSystem>(newEntity2);

	Gg::Entity newEntity3{engine.createEntity()};
	engine.createComponent<Gg::Component::SpriteComponent>(newEntity3, sf::Vector2f{550.f, 600.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Black.png");
	engine.addEntityToSystem<Gg::System::GraphicSystem>(newEntity3);

	Gg::Entity newEntity4{engine.createEntity()};
	engine.createComponent<Gg::Component::SpriteComponent>(newEntity4, sf::Vector2f{250.f, 600.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Red.png");
	engine.addEntityToSystem<Gg::System::GraphicSystem>(newEntity4);

	Gg::Entity newEntity5{engine.createEntity()};
	engine.createComponent<Gg::Component::SpriteComponent>(newEntity5, sf::Vector2f{150.f, 350.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Green.png");
	engine.addEntityToSystem<Gg::System::GraphicSystem>(newEntity5);

	while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))  {

            if (event.type == sf::Event::Closed) { window.close(); }
        }

        graphicSystem->update(0);
    }


	return 0;
}