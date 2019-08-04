#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/CharacterDraw.hpp"
#include "Systems/CharacterUpdate.hpp"

#include "Game/Camera.hpp"

#include "Components/Graphics/AnimationSet.hpp"

int main() {

	//sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Gulg v0.1", sf::Style::Default};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/GameSignatures")) {

		Camera currentView;

		CharacterUpdate updateChar{engine};
		CharacterDraw drawChar{window, engine};

		Gg::Entity character{engine.getNewEntity()};

		std::shared_ptr<Gg::Component::AnimationSet> anim{std::make_shared<Gg::Component::AnimationSet>()};
		anim->loadFromFile(engine, "Datas/CharAnimation.xml");
		engine.addComponentToEntity(character, "Animation", std::static_pointer_cast<Gg::Component::AbstractComponent>(anim));

		updateChar.addEntity(character);
		drawChar.addEntity(character);

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

	            if(event.type == sf::Event::KeyPressed) {

				    if(event.key.code == sf::Keyboard::Up) { anim->changeAnimation("TopWalk"); }
				    if(event.key.code == sf::Keyboard::Down) { anim->changeAnimation("BotWalk");}
				    if(event.key.code == sf::Keyboard::Left) { anim->changeAnimation("LeftWalk");}
				    if(event.key.code == sf::Keyboard::Right) { anim->changeAnimation("RightWalk");}
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