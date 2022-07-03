#include "GulgECS/GulgEngine.hpp"
#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/ComponentTypes.hpp"

#include <SFML/Graphics.hpp>

int main() {

	Gg::GulgEngine engine;

	Gg::Entity newEntity{engine.getNewEntity()};

	sf::RenderWindow window{sf::VideoMode{800, 600}, "Gulg Graphics"};

	while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))  {

            if (event.type == sf::Event::Closed) { window.close(); }
        }
    }


	return 0;
}