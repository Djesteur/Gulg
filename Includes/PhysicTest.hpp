#include <random>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/CharacterDraw.hpp"
#include "Systems/Graphics/PhysicTestDraw.hpp"
#include "Systems/CharacterUpdate.hpp"
#include "Systems/Physics/Physic.hpp"
#include "Systems/Physics/PhysicTest.hpp"

#include "Components/Graphics/AnimationSet.hpp"
#include "Components/Graphics/Shapes.hpp"
#include "Components/Physics/Hitbox.hpp"

std::vector<Gg::Entity> randomCircles(Gg::GulgEngine &engine, 
								  	Gg::Systems::Physic &physicSystem,
								  PhysicTestDraw &drawCircleTest,
								  Gg::Systems::PhysicTest &physicTestUpdates,
								  const unsigned int nbCircle);