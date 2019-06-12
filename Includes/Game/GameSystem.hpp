#ifndef GAME_SYSTEM_HPP
#define GAME_SYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "System.hpp"
#include "Graphics/SpriteAlgorithm.hpp"
#include "Game/TimerAlgorithm.hpp"

namespace Gg {

class GameSystem: public System {

	public:

		GameSystem(EntitySignatureKeeper &entitySignatureKeeper, SignatureLoader &signatureLoader, ComponentKeeper &componentKeeper);

		virtual ~GameSystem();

	protected:

};

}

#endif