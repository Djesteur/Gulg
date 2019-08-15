#include "PhysicTest.hpp"

std::vector<Gg::Entity> randomCircles(Gg::GulgEngine &engine, 
								  Gg::Systems::Physic &physicSystem,
								  PhysicTestDraw &drawCircleTest,
								  Gg::Systems::PhysicTest &physicTestUpdates,
								  const unsigned int nbCircle) {

	std::vector<Gg::Entity> result{nbCircle};

	std::default_random_engine randomEngine {static_cast<long unsigned int>(std::time(nullptr))};
    std::uniform_int_distribution<unsigned int> massRandom(1, 10); 
    std::uniform_int_distribution<unsigned char> colorRandom(0, 255);
    std::uniform_real_distribution<float> posXRandom(10, 150), posYRandom(15, 75);

	for(unsigned int i{0}; i < nbCircle; i++) {

		Gg::Entity currentEntity{engine.getNewEntity()};

		unsigned int objectMass{massRandom(randomEngine)};
		sf::Uint8 r{colorRandom(randomEngine)}, g{colorRandom(randomEngine)}, b{colorRandom(randomEngine)};
		float positionX{posXRandom(randomEngine)}, positionY{posYRandom(randomEngine)};

		std::shared_ptr<Gg::Component::Vector2D> graphicPosition{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> physicPosition{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> speed{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::UnsignedInt> mass{std::make_shared<Gg::Component::UnsignedInt>(objectMass)};
		engine.addComponentToEntity(currentEntity, "GraphicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(graphicPosition));
		engine.addComponentToEntity(currentEntity, "PhysicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(physicPosition));
		engine.addComponentToEntity(currentEntity, "Speed", std::static_pointer_cast<Gg::Component::AbstractComponent>(speed));
		engine.addComponentToEntity(currentEntity, "Mass", std::static_pointer_cast<Gg::Component::AbstractComponent>(mass));

		std::shared_ptr<Gg::Component::CircleHitbox> hitbox{std::make_shared<Gg::Component::CircleHitbox>()};
		std::shared_ptr<Gg::Component::CircleShape> graphicHitbox{std::make_shared<Gg::Component::CircleShape>()};
		engine.addComponentToEntity(currentEntity, "Hitbox", std::static_pointer_cast<Gg::Component::AbstractComponent>(hitbox));
		engine.addComponentToEntity(currentEntity, "GraphicHitbox", std::static_pointer_cast<Gg::Component::AbstractComponent>(graphicHitbox));

		physicPosition->value = sf::Vector2f{positionX, positionY};
		graphicPosition->value = sf::Vector2f{physicPosition->value.x*8, physicPosition->value.y*8};
		speed->value = sf::Vector2f{0, 0};

		hitbox->centerPosition.value = physicPosition->value;
		hitbox->radius = static_cast<float>(mass->value);

		sf::CircleShape newShape;
		newShape.setRadius(hitbox->radius*8.f);
		newShape.setOrigin(hitbox->radius*8.f, hitbox->radius*8.f);
		newShape.setFillColor(sf::Color{r, g, b});
		graphicHitbox->shape = std::make_unique<sf::CircleShape>(newShape);
		

		physicSystem.addEntity(currentEntity);
		drawCircleTest.addEntity(currentEntity);
		physicTestUpdates.addEntity(currentEntity);

		result.emplace_back(currentEntity);
	}

	return result;
}