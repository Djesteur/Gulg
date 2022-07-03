#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"

#include <SFML/Graphics.hpp>

void registerComponents(Gg::GulgEngine &engine) {

	engine.registerComponent(std::make_shared<SpriteComponent>());
}

int main() {

	Gg::GulgEngine engine;

	registerComponents(engine);

	Gg::Entity newEntity{engine.getNewEntity()};
	engine.addComponentToEntity(newEntity, engine.createComponent(Component::Type::Sprite));

	sf::RenderWindow window{sf::VideoMode{800, 600}, "Gulg Graphics"};



	while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))  {

            if (event.type == sf::Event::Closed) { window.close(); }
        }
    }


	return 0;
}