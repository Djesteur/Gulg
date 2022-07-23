#ifndef COMPONENT_KEEPER_HPP
#define COMPONENT_KEEPER_HPP

#include <string>
#include <map>
#include <memory>

#include "GulgECS/GulgDeclarations.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/Signature.hpp"

using namespace Gg::Component;

namespace Gg {

class ComponentKeeper {

	public:

		ComponentKeeper();

		void addEntity(const Entity entity);
		void deleteEntity(const Entity entity);


		template<ComponentConstraint T, typename... Args>
		std::shared_ptr<AbstractComponent> createComponent(const Entity entity, Args&&... args) {

			if(!entityExist(entity)) { addEntity(entity); }

			if(!entityHasComponent<T>(entity)) {

				std::shared_ptr<T> newComponent = std::make_shared<T>(args...);
				m_components[entity].insert(std::make_pair(T::getType(), newComponent));
				return newComponent;
			}

			return nullptr;
		}


		template<ComponentConstraint T>
		void deleteComponent(const Entity entity) { deleteComponent(entity, T::getType()); }
		void deleteComponent(const Entity entity, const Type type);

		bool entityExist(const Entity entity) const;

		template<ComponentConstraint T>
		bool entityHasComponent(const Entity entity) { return entityHasComponent(entity, T::getType()); }
		bool entityHasComponent(const Entity entity, const Type type) const;

		void cloneEntity(const Entity entityToClone, const Entity clone);
		

		template<ComponentConstraint T>
		std::shared_ptr<T> getComponent(const Entity entity) { return std::static_pointer_cast<T>(getComponent(entity, T::getType())); }
		std::shared_ptr<AbstractComponent> getComponent(const Entity entity, const Type type) const;


	private:

		std::map<Entity, std::map<Type, std::shared_ptr<AbstractComponent>>> m_components;
                              
};

}

#endif