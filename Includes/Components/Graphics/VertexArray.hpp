#ifndef VERTEX_ARRAY_COMPONENT_HPP
#define VERTEX_ARRAY_COMPONENT_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include "Components/Component.hpp"

namespace Gg {

namespace Component {

struct VertexArray: public AbstractComponent {

	public:

		VertexArray(): texture{nullptr} {}
		VertexArray(const VertexArray &component): 
			vertexArray{component.vertexArray},
			texture{component.texture} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<VertexArray>(*this)); }

		sf::VertexArray vertexArray;
		sf::Texture *texture;           
};

}}

#endif