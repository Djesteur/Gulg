#include "GulgECS/Components/Position.hpp"

namespace Gg {

namespace Component {

Position::Position(): m_position{0.f, 0.f} {}

Position::Position(const float x, const float y): Position(glm::vec2{x, y}) {}

Position::Position(const glm::vec2 position): m_position{position} {}

void Position::setPosition(const float newX, const float newY) { setPosition(glm::vec2{newX, newY}); }

void Position::setPosition(const glm::vec2 newPosition) { m_position = newPosition;}

void Position::move(const float x, const float y) { move(glm::vec2{x, y}); }

void Position::move(const glm::vec2 movement) { m_position += movement; }

float Position::getX() const { return m_position.x; }

float Position::getY() const { return m_position.y; }

glm::vec2 Position::getPosition() const { return m_position; }

std::shared_ptr<AbstractComponent> Position::clone() const { return std::make_shared<Position>(m_position); }

}

}