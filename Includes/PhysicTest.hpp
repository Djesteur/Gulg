#include <random>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/CharacterDraw.hpp"
#include "Systems/Graphics/PhysicTestDrawCircle.hpp"
#include "Systems/CharacterUpdate.hpp"
#include "Systems/Physics/Physic.hpp"
#include "Systems/Physics/PhysicTest.hpp"

#include "Components/Graphics/AnimationSet.hpp"
#include "Components/Graphics/CircleShape.hpp"
#include "Components/Physics/Hitbox.hpp"

std::vector<Gg::Entity> randomCircles(Gg::GulgEngine &engine, 
								  	Gg::Systems::Physic &physicSystem,
								  PhysicTestDrawCircle &drawCircleTest,
								  Gg::Systems::PhysicTest &physicTestUpdates,
								  const unsigned int nbCircle);