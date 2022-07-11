#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

#include "GulgGraphics/GraphicSystem.hpp"
#include "GulgGraphics/SpriteComponent.hpp"

#include <SFML/Graphics.hpp>

int main() {

	Gg::GulgEngine engine;


	sf::RenderWindow window{sf::VideoMode{800, 600}, "Gulg Graphics"};

	Gg::System::GraphicSystem graphicSystem(engine, window);
	engine.addSystem(graphicSystem);



	Gg::Entity newEntity1{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity1, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{10.f, 20.f}));
	graphicSystem.addEntity(newEntity1, engine.getEntitySignature(newEntity1));

	Gg::Entity newEntity2{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity2, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{100.f, 200.f}));
	graphicSystem.addEntity(newEntity2, engine.getEntitySignature(newEntity2));

	Gg::Entity newEntity3{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity3, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{50.f, 100.f}));
	graphicSystem.addEntity(newEntity3, engine.getEntitySignature(newEntity3));

	Gg::Entity newEntity4{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity4, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{200.f, 400.f}));
	graphicSystem.addEntity(newEntity4, engine.getEntitySignature(newEntity4));

	Gg::Entity newEntity5{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity5, std::make_shared<Gg::Component::SpriteComponent>(sf::Vector2f{400.f, 400.f}));
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