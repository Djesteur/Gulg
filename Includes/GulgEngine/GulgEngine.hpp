#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

#include "GulgEngine/GulgDeclarations.hpp"

#include "GulgEngine/EntityCreator.hpp"
#include "GulgEngine/EntitySignatureKeeper.hpp"
#include "GulgEngine/ComponentKeeper.hpp"

#include "Components/Component.hpp"

namespace Gg {

class GulgEngine {

	public:

		GulgEngine();

		bool loadSignatures(const std::string path);

		Entity getNewEntity();
		void deleteEntity(const Entity entity);

		void addComponentToEntity(const Entity entity, const ComponentType type, std::shared_ptr<Component::AbstractComponent> component);

		template <typename T>
		void addComponentToEntity(const Entity entity, const ComponentType type, std::shared_ptr<T> component) {

			addComponentToEntity(entity, type, std::static_pointer_cast<Component::AbstractComponent>(component));
		}

		void deleteComponentToEntity(const Entity entity, const ComponentType type);
		bool entityHasComponent(const Entity entity, const ComponentType type);

		Signature getEntitySignature(const Entity entity) const;

		std::shared_ptr<Component::AbstractComponent> getComponent(const Entity entity, const ComponentType type) const;

		template <typename T>
		std::shared_ptr<T> getComponent(const Entity entity, const ComponentType type) const {


			return std::static_pointer_cast<T>(m_componentKeeper.getComponent(entity, type));
		}

		Entity cloneEntity(const Entity entityToClone);

	private:

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;                        
};

}

#endif