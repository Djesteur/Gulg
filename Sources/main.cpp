#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "EntityCreator.hpp"
#include "EntitySignatureKeeper.hpp"
#include "SignatureLoader.hpp"
#include "ComponentKeeper.hpp"
#include "Component.hpp"

#include "Graphics/TileDrawSystem.hpp"

#include "MapConstruction.hpp"

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Gulg v0.1", sf::Style::Default, settings};

	Gg::SignatureLoader loader;
	if(loader.loadFile("TestSignatures")) {

		Gg::EntityCreator entityCreator;
		Gg::EntitySignatureKeeper entitySignatureKeeper{loader.getNumberOfSignatures()};
		Gg::ComponentKeeper componentKeeper;

		Gg::TileDrawSystem tileDraw{window, entitySignatureKeeper, loader, componentKeeper};

		for(unsigned int x{0}; x < 21; x++) {
			for(unsigned int y{0}; y < 19; y++) {

				tileDraw.addEntity(constructHexaTile(256, x, y, entityCreator, entitySignatureKeeper, componentKeeper, loader));
			}
		}


		sf::View currentView{sf::Vector2f{0, 0}, sf::Vector2f{1280, 720}};

		bool movingMouseMap{false};
		float moveView{1.f};

		const unsigned int minZoom{1}, maxZoom{15};
		unsigned int currentZoom{15};
		sf::Vector2i oldMousePosition, newMousePosition;

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

		        if(event.type == sf::Event::MouseWheelScrolled) {

					if(event.mouseWheelScroll.delta > 0) { 

						if(currentZoom < maxZoom) {

							currentView.zoom(0.8f); 
							moveView *= 0.8f; 
							currentZoom++;
						}
					}

					if(event.mouseWheelScroll.delta < 0) { 

						if(currentZoom > minZoom) {

							currentView.zoom(1.25f); 
							moveView *= 1.25f; 
							currentZoom--;
						}
					}
				}

				if(event.type == sf::Event::MouseButtonPressed) {

					if(event.mouseButton.button == sf::Mouse::Left) { movingMouseMap = true; oldMousePosition = sf::Mouse::getPosition(); } 
				}

				if(event.type == sf::Event::MouseButtonReleased) {

					if(event.mouseButton.button == sf::Mouse::Left) { movingMouseMap = false; } 
				}
			}

			//Update

			if(movingMouseMap) {

				newMousePosition = sf::Mouse::getPosition();
				currentView.move((oldMousePosition.x - newMousePosition.x)*moveView, (oldMousePosition.y - newMousePosition.y)*moveView);
				oldMousePosition = newMousePosition;
			}

			//Draw

	        window.clear(sf::Color::Black);
	        window.setView(currentView);
	        tileDraw.applyAlgorithms();
	        window.setView(window.getDefaultView());
	        window.display();
	    }
	}

	return 0;
}