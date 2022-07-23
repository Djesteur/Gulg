#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <string>

#include "GulgECS/AbstractComponent.hpp"

#include <SFML/Graphics.hpp>

namespace Gg {

namespace Component {

class SpriteComponent: public AbstractComponent, public sf::Drawable {

	public:


		SpriteComponent();
		SpriteComponent(sf::Vector2f position, std::string texturePath);

		virtual std::shared_ptr<AbstractComponent> clone() const;

		static Component::Type getType() { return Component::Type::SpriteComponent; }

	private:

		sf::Texture m_texture;
		sf::Sprite m_sprite;

    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;              
};

}

}

#endif