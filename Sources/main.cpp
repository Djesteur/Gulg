#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/CharacterDrawSystem.hpp"
#include "Systems/CharacterUpdate.hpp"

#include "Game/Camera.hpp"

#include "Game/EntityObject/AnimationSet.hpp"

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Gulg v0.1", sf::Style::Default, settings};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/GameSignatures") && engine.loadTexture("charSprite", "Datas/Char.png")) {

		Camera currentView;

		CharacterUpdate updateChar{engine};
		CharacterDrawSystem drawChar{window, engine};

		Gg::Entity anim = Gg::Object::loadAnimationSetFromFile(engine, "Datas/CharAnimation.xml");

		updateChar.addEntity(anim);
		drawChar.addEntity(anim);

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

	            if(event.type == sf::Event::KeyPressed) {
				    if(event.key.code == sf::Keyboard::Up) { Gg::Object::changeAnimation(engine, anim, "TopWalk"); }
				    if(event.key.code == sf::Keyboard::Down) {Gg::Object::changeAnimation(engine, anim, "BotWalk");}
				    if(event.key.code == sf::Keyboard::Left) {Gg::Object::changeAnimation(engine, anim, "LeftWalk");}
				    if(event.key.code == sf::Keyboard::Right) {Gg::Object::changeAnimation(engine, anim, "RightWalk");}
				}
			}

			//Update

			updateChar.applyAlgorithms();

			//Draw

	        window.clear(sf::Color::Black);
	        window.setView(currentView);
	        window.setView(window.getDefaultView());
	        drawChar.applyAlgorithms();
	        window.display();
	    }
	}

	return 0;
}