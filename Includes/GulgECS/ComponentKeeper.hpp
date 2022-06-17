#ifndef COMPONENT_KEEPER_HPP
#define COMPONENT_KEEPER_HPP

#include <string>
#include <map>
#include <memory>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/Signature.hpp"

namespace Gg {

class ComponentKeeper {

	public:

		ComponentKeeper();

		void addEntity(const Entity entity);
		void addComponent(const Entity entity, std::shared_ptr<Component::AbstractComponent> newComponent);

		void deleteEntity(const Entity entity);
		void deleteComponent(const Entity entity, const Component::Type type);

		bool entityExist(const Entity entity) const;
		bool entityHasComponent(const Entity entity, const Component::Type type) const;

		void cloneEntity(const Entity entityToClone, const Entity clone);
		

		std::shared_ptr<Component::AbstractComponent> getComponent(const Entity entity, const Component::Type type) const;


	private:

		std::map<Entity, std::map<Component::Type, std::shared_ptr<Component::AbstractComponent>>> m_components;
                              
};

}

#endif