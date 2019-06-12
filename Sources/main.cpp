#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "EntityCreator.hpp"
#include "EntitySignatureKeeper.hpp"
#include "ComponentKeeper.hpp"
#include "Component.hpp"

#include "Graphics/GraphicSystem.hpp"
#include "Graphics/SpriteComponent.hpp"

#include "Game/GameSystem.hpp"
#include "Game/TimerComponent.hpp"

int main() {

	sf::RenderWindow window{sf::VideoMode{800, 800}, "Gulg v0.1"};

	Gg::SignatureLoader loader;
	sf::Texture texture; 
	if(loader.loadFile("TestSignatures") && texture.loadFromFile("Datas/Ocean.png") ) {

		Gg::EntityCreator entityCreator;
		Gg::EntitySignatureKeeper entitySignatureKeeper{loader.getNumberOfSignatures()};
		Gg::ComponentKeeper componentKeeper;

		Gg::GraphicSystem graphicSystem{window, entitySignatureKeeper, loader, componentKeeper};

		Gg::Entity firstEntity{entityCreator.createEntity()};

		componentKeeper.addEntity(firstEntity);
		std::shared_ptr<Gg::SpriteComponent> firstComponent{std::make_shared<Gg::SpriteComponent>()};

		firstComponent->sprite.setTexture(texture);
		firstComponent->sprite.setPosition(128, 128);

		componentKeeper.addComponent(firstEntity, std::string{"MainSprite"}, std::static_pointer_cast<Gg::Component>(firstComponent));

		entitySignatureKeeper.addEntity(firstEntity);
		entitySignatureKeeper.addToSignature(firstEntity, loader.getSignature("MainSprite"));

		graphicSystem.addEntity(firstEntity);

		Gg::GameSystem gameSystem{entitySignatureKeeper, loader, componentKeeper};

		std::shared_ptr<Gg::TimerComponent> firstTimerComponent{std::make_shared<Gg::TimerComponent>(1'750'000)};
		componentKeeper.addComponent(firstEntity, std::string{"SpawnTimer"}, std::static_pointer_cast<Gg::Component>(firstTimerComponent));
		entitySignatureKeeper.addToSignature(firstEntity, loader.getSignature("SpawnTimer"));
		gameSystem.addEntity(firstEntity);

		while(window.isOpen()) {

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }
	        }

	        gameSystem.applyAlgorithms();

	        window.clear(sf::Color::Black);

	        graphicSystem.applyAlgorithms();

	        window.display();
	    }
	}

	return 0;
}