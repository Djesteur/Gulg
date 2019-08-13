#include "PhysicTest.hpp"

std::vector<Gg::Entity> randomCircles(Gg::GulgEngine &engine, 
								  Gg::Systems::Physic &physicSystem,
								  PhysicTestDrawCircle &drawCircleTest,
								  Gg::Systems::PhysicTest &physicTestUpdates,
								  const unsigned int nbCircle) {

	std::vector<Gg::Entity> result{nbCircle};

	std::default_random_engine randomEngine { std::time(nullptr) };
    std::uniform_int_distribution<unsigned int> massRandom(1, 10), colorRandom(0, 255);
    std::uniform_real_distribution<float> posXRandom(10, 150), posYRandom(15, 75);

	for(unsigned int i{0}; i < nbCircle; i++) {

		Gg::Entity currentEntity{engine.getNewEntity()};

		unsigned int mass{massRandom(randomEngine)};
		sf::Uint8 r{colorRandom(randomEngine)}, g{colorRandom(randomEngine)}, b{colorRandom(randomEngine)};
		float positionX{posXRandom(randomEngine)}, positionY{posYRandom(randomEngine)};

		std::shared_ptr<Gg::Component::Vector2D> graphicPositionTest1{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> physicPositionTest1{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::Vector2D> speedTest1{std::make_shared<Gg::Component::Vector2D>()};
		std::shared_ptr<Gg::Component::UnsignedInt> massTest1{std::make_shared<Gg::Component::UnsignedInt>(mass)};
		engine.addComponentToEntity(currentEntity, "GraphicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(graphicPositionTest1));
		engine.addComponentToEntity(currentEntity, "PhysicPosition", std::static_pointer_cast<Gg::Component::AbstractComponent>(physicPositionTest1));
		engine.addComponentToEntity(currentEntity, "Speed", std::static_pointer_cast<Gg::Component::AbstractComponent>(speedTest1));
		engine.addComponentToEntity(currentEntity, "Mass", std::static_pointer_cast<Gg::Component::AbstractComponent>(massTest1));

		std::shared_ptr<Gg::Component::CircleHitbox> hitboxTest1{std::make_shared<Gg::Component::CircleHitbox>()};
		std::shared_ptr<Gg::Component::CircleShape> graphicHitboxTest1{std::make_shared<Gg::Component::CircleShape>()};
		engine.addComponentToEntity(currentEntity, "Hitbox", std::static_pointer_cast<Gg::Component::AbstractComponent>(hitboxTest1));
		engine.addComponentToEntity(currentEntity, "GraphicHitbox", std::static_pointer_cast<Gg::Component::AbstractComponent>(graphicHitboxTest1));

		physicPositionTest1->value = sf::Vector2f{positionX, positionY};
		graphicPositionTest1->value = sf::Vector2f{physicPositionTest1->value.x*8, physicPositionTest1->value.y*8};
		speedTest1->value = sf::Vector2f{0, 0};

		hitboxTest1->centerPosition.value = physicPositionTest1->value;
		graphicHitboxTest1->circle.setPosition(graphicPositionTest1->value);

		hitboxTest1->radius = static_cast<float>(mass);
		graphicHitboxTest1->circle.setRadius(hitboxTest1->radius*8.f);
		graphicHitboxTest1->circle.setOrigin(hitboxTest1->radius*8.f, hitboxTest1->radius*8.f);
		graphicHitboxTest1->circle.setFillColor(sf::Color{r, g, b});

		physicSystem.addEntity(currentEntity);
		drawCircleTest.addEntity(currentEntity);
		physicTestUpdates.addEntity(currentEntity);

		result.emplace_back(currentEntity);
	}

	return result;
}