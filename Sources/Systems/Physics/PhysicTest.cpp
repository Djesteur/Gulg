#include "Systems/Physics/PhysicTest.hpp"

namespace Gg {

namespace Systems {

PhysicTest::PhysicTest(GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<Gg::Algorithm::SynchronizePositions>(gulgEngine, 8));
}

PhysicTest::~PhysicTest() {}

}}