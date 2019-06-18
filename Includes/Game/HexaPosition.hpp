#ifndef HEXA_POSITION_COMPONENT_HPP
#define HEXA_POSITION_COMPONENT_HPP

#include "Component.hpp"

namespace Gg {

struct HexaPosition: public Component {

	HexaPosition():
		x{0},
		y{0},
		z{0} {}

	HexaPosition(const unsigned int inX,const unsigned int inY):
		x{inX},
		y{inY},
		z{- (x + y)} {}

	HexaPosition(const unsigned int inX,const unsigned int inY, const unsigned int inZ):
		x{inX},
		y{inY},
		z{inZ} {}

	HexaPosition(const TimerComponent &component):
		x{component.x},
		y{component.y},
		z{component.z} {}

	virtual std::shared_ptr<Component> clone() const { return std::static_pointer_cast<Component>(std::make_shared<HexaPosition>(*this)); }

	void setPosition(const unsigned int inX, const unsigned int inY) {

		x = inX;
		y = inY;
		z = - (x + y);
	}

	void move(const unsigned int inX, const unsigned int inY) {

		x += inX;
		y += inY;
		z = - (x + y);
	}

	unsigned int distanceTo(const HexaPosition &otherPosition) { return (abs(otherPosition.x - x) + abs(otherPosition.y - y) abs(otherPosition.y - y))/2; }

	unsigned int x, y, z;         
};

}

#endif