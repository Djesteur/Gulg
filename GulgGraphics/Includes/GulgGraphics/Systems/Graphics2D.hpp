#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include "GulgECS/Signature.hpp"
#include "GulgECS/AbstractSystem.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"
#include "GulgECS/GulgEngine.hpp"

#include <SFML/Graphics.hpp>

#include "GulgGraphics/GulgGraphicsDeclarations.hpp"
#include "GulgGraphics/Components/Sprite.hpp"

namespace Gg {

namespace System {

/**
 * @brief      A graphic system
 */
class Graphics2D: public AbstractSystem {

	public:

		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param      keeper  The keeper
		 * @param      window  The window
		 */
		Graphics2D(ComponentKeeper &keeper, sf::RenderWindow &window);

		/**
		 * @brief      Updates the given delta time.
		 *
		 * @param[in]  deltaTime  The delta time
		 */
		virtual void update(const double deltaTime);

	private:

		sf::RenderWindow &m_renderWindow;
};

}

}

#endif