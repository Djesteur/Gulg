#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include "GulgECS/Signature.hpp"
#include "GulgECS/AbstractSystem.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"
#include "GulgECS/GulgEngine.hpp"

#include <SFML/Graphics.hpp>

#include "GulgGraphics/SpriteComponent.hpp"

namespace Gg {

namespace System {

class GraphicSystem: public AbstractSystem {

	public:

		GraphicSystem(GulgEngine &engine, sf::RenderWindow &renderWindow);

		virtual void update(const double deltaTime);

	protected:

		sf::RenderWindow &m_renderWindow;
};

}

}

#endif