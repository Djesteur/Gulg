#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/CharacterDraw.hpp"
#include "Systems/CharacterUpdate.hpp"

#include "Game/Camera.hpp"

#include "Components/Graphics/AnimationSet.hpp"

#include "Systems/Physics/Physic.hpp"

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Gulg v0.1", sf::Style::Default};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/GameSignatures")) {

		Camera currentView;

		CharacterUpdate updateChar{engine};
		CharacterDraw drawChar{window, engine};
		Physic physicSystem{engine};

		Gg::Entity character{engine.getNewEntity()};

		std::shared_ptr<Gg::Component::AnimationSet> anim{std::make_shared<Gg::Component::AnimationSet>()};
		if(!anim->loadFromFile(engine, "Datas/CharAnimation.xml")) { return 0; }

		engine.addComponentToEntity(character, "Animation", std::static_pointer_cast<Gg::Component::AbstractComponent>(anim));
		anim->changeAnimation("BotWait");

		std::shared_ptr<Gg::Component::Vector2D> graphicPosition{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> physicPosition{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> speed{std::make_shared<Gg::Component::Vector2D>()};
		engine.addComponentToEntity(character, "GraphicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(graphicPosition));
		engine.addComponentToEntity(character, "PhysicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(physicPosition));
		engine.addComponentToEntity(character, "Speed", std::static_pointer_cast<Gg::Component::AbstractComponent>(speed));
		

		

		physicSystem.addEntity(character);
		updateChar.addEntity(character);
		drawChar.addEntity(character);

		bool pressedUp{false}, pressedDown{false}, pressedLeft{false}, pressedRight{false};

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

	            if(event.type == sf::Event::KeyPressed) {

	            	std::shared_ptr<Gg::Component::Vector2D> charSpeed{ 
						std::static_pointer_cast<Gg::Component::Vector2D>(engine.getComponent(character, "Speed"))
					};

				    if(event.key.code == sf::Keyboard::Up) { 
 
				    	if(!pressedUp) { 

				    		pressedUp = true;
				    		charSpeed->value += sf::Vector2f{0.f, -16.f};
				    		anim->changeAnimation("TopWalk");
				    	}

				    }

				    if(event.key.code == sf::Keyboard::Down) { 

				    	if(!pressedDown) { 

				    		pressedDown = true;
				    		charSpeed->value += sf::Vector2f{0.f, 16.f};
				    		anim->changeAnimation("BotWalk");
				    	}
				    }

				    if(event.key.code == sf::Keyboard::Left) { 

				    	if(!pressedLeft) { 

				    		pressedLeft = true;
				    		charSpeed->value += sf::Vector2f{-16.f, 0.f};
				    		anim->changeAnimation("LeftWalk");
				    	}
				    }

				    if(event.key.code == sf::Keyboard::Right) { 

				    	if(!pressedRight) { 

				    		pressedRight = true;
				    		charSpeed->value += sf::Vector2f{16.f, 0.f};
				    		anim->changeAnimation("RightWalk");
				    	}
				    }
				}

				if(event.type == sf::Event::KeyReleased) {

	            	std::shared_ptr<Gg::Component::Vector2D> charSpeed{ 
						std::static_pointer_cast<Gg::Component::Vector2D>(engine.getComponent(character, "Speed"))
					};

				    if(event.key.code == sf::Keyboard::Up) { 

				    	anim->changeAnimation("TopWait"); 
				    	charSpeed->value -= sf::Vector2f{0.f, -16.f};
				    	pressedUp = false;
				    }

				    if(event.key.code == sf::Keyboard::Down) { 

				    	anim->changeAnimation("BotWait");
				    	charSpeed->value -= sf::Vector2f{0.f, 16.f};
				    	pressedDown = false;
				    }

				    if(event.key.code == sf::Keyboard::Left) { 

				    	anim->changeAnimation("LeftWait");
				    	charSpeed->value -= sf::Vector2f{-16.f, 0.f};
				    	pressedLeft = false;
				    }

				    if(event.key.code == sf::Keyboard::Right) { 

				    	anim->changeAnimation("RightWait");
				    	charSpeed->value -= sf::Vector2f{16.f, 0.f};
				    	pressedRight = false;
				    }
				}
			}

			//Update

			physicSystem.applyAlgorithms();
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

/*

	- Position
	- Vitesse
	- Masse
	- Hitbox
	
*/