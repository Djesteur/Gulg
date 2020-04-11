#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

#include <GL/glew.h>
#include <GL/gl.h>

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
		void deleteComponentToEntity(const Entity entity, const ComponentType type);
		bool entityHasComponent(const Entity entity, const ComponentType type);

		Signature getEntitySignature(const Entity entity) const;

		std::shared_ptr<Component::AbstractComponent> getComponent(const Entity entity, const ComponentType type) const;

		Entity cloneEntity(const Entity entityToClone);

	private:

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;                        
};

}

#endif