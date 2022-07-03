#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

#include "GulgECS/GulgDeclarations.hpp"

#include "GulgECS/EntityCreator.hpp"
#include "GulgECS/EntitySignatureKeeper.hpp"
#include "GulgECS/ComponentKeeper.hpp"
#include "GulgECS/ComponentSignatureKeeper.hpp"
#include "GulgECS/AbstractComponent.hpp"
#include "GulgECS/AbstractSystem.hpp"

#include "GulgECS/Logger.hpp"

namespace Gg {

class GulgEngine {

	public:

		GulgEngine(const bool wantLogs = false, const std::string logFilePath = "LogFile.log");

		Entity getNewEntity();
		void deleteEntity(const Entity entity);

		void addComponentToEntity(const Entity entity, std::shared_ptr<Component::AbstractComponent> component);
		void deleteComponentToEntity(const Entity entity, std::shared_ptr<Component::AbstractComponent> component);
		void deleteComponentToEntity(const Entity entity, const Component::Type type);

		bool entityHasComponent(const Entity entity, const Component::Type type);

		Signature getEntitySignature(const Entity entity) const;

		std::shared_ptr<Component::AbstractComponent> getComponent(const Entity entity, const Component::Type type) const;


		Entity cloneEntity(const Entity entityToClone);

		void addSystem(System::AbstractSystem &systemToAdd);
		void deleteSystem(System::AbstractSystem &systemToDelete);



	private:

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;    
		
		std::vector<std::reference_wrapper<System::AbstractSystem>> m_systems;                 
};

}

#endif