#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

#include "GulgGraphics/GraphicSystem.hpp"
#include "GulgGraphics/SpriteComponent.hpp"

#include <SFML/Graphics.hpp>

int main() {

	Gg::GulgEngine engine;


	sf::RenderWindow window{sf::VideoMode{800, 800}, "Gulg Graphics"};

	Gg::System::GraphicSystem graphicSystem(engine, window);
	engine.addSystem(graphicSystem);



	Gg::Entity newEntity1{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity1, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{400.f, 200.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/White.png"));
	graphicSystem.addEntity(newEntity1, engine.getEntitySignature(newEntity1));

	Gg::Entity newEntity2{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity2, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{650.f, 350.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Blue.png"));
	graphicSystem.addEntity(newEntity2, engine.getEntitySignature(newEntity2));

	Gg::Entity newEntity3{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity3, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{550.f, 600.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Black.png"));
	graphicSystem.addEntity(newEntity3, engine.getEntitySignature(newEntity3));

	Gg::Entity newEntity4{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity4, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{250.f, 600.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Red.png"));
	graphicSystem.addEntity(newEntity4, engine.getEntitySignature(newEntity4));

	Gg::Entity newEntity5{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity5, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{150.f, 350.f} - sf::Vector2f{32, 32}, "GulgGraphics/Datas/Green.png"));
	graphicSystem.addEntity(newEntity5, engine.getEntitySignature(newEntity5));

	while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))  {

            if (event.type == sf::Event::Closed) { window.close(); }
        }

        graphicSystem.update(0);
    }


	return 0;
}