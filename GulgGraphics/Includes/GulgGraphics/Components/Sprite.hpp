#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <string>

#include "GulgECS/AbstractComponent.hpp"

#include <SFML/Graphics.hpp>

namespace Gg {

namespace Component {

/**
 * @brief      This class describes a sprite component.
 */
class Sprite: public AbstractComponent, public sf::Drawable {

	public:


		/**
		 * @brief      Constructs a new instance.
		 */
		Sprite();
		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param[in]  position     The position
		 * @param[in]  texturePath  The texture path
		 */
		Sprite(sf::Vector2f position, std::string texturePath);

		/**
		 * @brief      Creates a new instance of the object with same properties than original.
		 *
		 * @return     Copy of this object.
		 */
		virtual std::shared_ptr<AbstractComponent> clone() const;

		STATIC_GET_TYPE(Drawable)

	private:

		sf::Texture m_texture;
		sf::Sprite m_sprite;

    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;              
};

}

}

#endif