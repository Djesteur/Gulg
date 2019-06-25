#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/TileDrawSystem.hpp"

#include "Game/MapConstruction.hpp"

#include "Game/Camera.hpp"

bool isLeftTurn(const sf::Vector2f p1, const sf::Vector2f p2, const sf::Vector2f p3) {

	sf::Vector2f v1{p2.x - p1.x, p2.y - p1.y};
	sf::Vector2f v2{p3.x - p2.x, p3.y - p2.y};

	if(v1.x*v2.y-v2.x*v1.y > 0) { return false; }
	else { return true; }
}

Gg::Entity findSelection(const std::vector<Gg::Entity> map, 
						 const sf::Vector2f mouseWorldPostion,
						 Gg::GulgEngine &engine) {

	bool allRightTurn{true};

	for(Gg::Entity currentEntity: map) {

		std::shared_ptr<Gg::VertexArrayComponent> currentArray{
			std::static_pointer_cast<Gg::VertexArrayComponent>(engine.getComponent(currentEntity, "TileCenterVertex"))
		};
		allRightTurn = true;

		for(size_t i{1}; i < 7; i++) {

			if(!isLeftTurn(currentArray->vertexArray[i].position,
						   currentArray->vertexArray[i+1].position,
						   sf::Vector2f{mouseWorldPostion.x, mouseWorldPostion.y})) { 

				allRightTurn = false;
			}

		}

		if(allRightTurn) { return currentEntity; }
	}

	return 0;
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Gulg v0.1", sf::Style::Default, settings};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("GameSignatures")) {

		TileDrawSystem tileDraw{window, engine};

		std::vector<Gg::Entity> map{constructMap(256, 21, 19, engine)};

		for(Gg::Entity currentTile: map) { tileDraw.addEntity(currentTile); }


		Camera currentView;

		

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

				currentView.applyEvents(event);

				if(event.type == sf::Event::MouseButtonReleased) {
					if(event.mouseButton.button == sf::Mouse::Left) { 

						Gg::Entity selectedEntity{findSelection(map, window.mapPixelToCoords(sf::Mouse::getPosition(window), currentView), engine)};
						if(selectedEntity != 0) {

							for(Gg::Entity currentEntity: map) {

								std::shared_ptr<Gg::BooleanComponent> isSelectedBorderArray{
									std::static_pointer_cast<Gg::BooleanComponent>(engine.getComponent(currentEntity, "IsTileSelectedBorderVertex"))
								};

								if(currentEntity == selectedEntity) { isSelectedBorderArray->value = true; }
								else { isSelectedBorderArray->value = false; }
								
							}
						} 
					} 
				}
			}

			//Update

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