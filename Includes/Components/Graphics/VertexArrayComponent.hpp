#ifndef VERTEX_ARRAY_COMPONENT_HPP
#define VERTEX_ARRAY_COMPONENT_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include "Components/Component.hpp"

namespace Gg {

struct VertexArrayComponent: public Component {

	public:

		VertexArrayComponent(): texture{nullptr} {}
		VertexArrayComponent(const VertexArrayComponent &component): 
			vertexArray{component.vertexArray},
			texture{component.texture} {}

		virtual std::shared_ptr<Component> clone() const { return std::static_pointer_cast<Component>(std::make_shared<VertexArrayComponent>(*this)); }

		sf::VertexArray vertexArray;
		sf::Texture *texture;           
};

}

#endif