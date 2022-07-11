#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "GulgECS/AbstractComponent.hpp"

#include <SFML/Graphics.hpp>

namespace Gg {

namespace Component {

class SpriteComponent: public AbstractComponent, public sf::Drawable {

	public:

		SpriteComponent(sf::Vector2f position);

		virtual std::shared_ptr<AbstractComponent> clone() const;

	private:

		sf::Texture m_texture;
		sf::Sprite m_sprite;

    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;              
};

}

}

#endif