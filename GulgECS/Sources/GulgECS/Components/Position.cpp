#include "GulgECS/Components/Position.hpp"

namespace Gg {

namespace Component {

Position::Position(): X{0}, Y{0} {}

Position::Position(double x, double y): X{x}, Y{y} {}


std::shared_ptr<AbstractComponent> Position::clone() const { return std::make_shared<Position>(X, Y); }

}

}