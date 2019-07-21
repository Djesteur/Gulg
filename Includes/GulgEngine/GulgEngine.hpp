#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

#include "GulgEngine/EntityCreator.hpp"
#include "GulgEngine/EntitySignatureKeeper.hpp"
#include "GulgEngine/SignatureLoader.hpp"
#include "GulgEngine/ComponentKeeper.hpp"
#include "GulgEngine/TextureKeeper.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

#include "Components/Component.hpp"



namespace Gg {

class GulgEngine {

	public:

		GulgEngine();

		bool loadSignatures(const std::string path);

		Entity getNewEntity();
		void deleteEntity(const Entity entity);

		void addComponentToEntity(const Entity entity, const std::string name, std::shared_ptr<AbstractComponent> component);
		void deleteComponentToEntity(const Entity entity, const std::string name);
		bool entityHasComponent(const Entity entity, const std::string name);

		Signature getEntitySignature(const Entity entity) const;

		std::shared_ptr<AbstractComponent> getComponent(const Entity entity, const std::string name) const;
		Signature getComponentSignature(const std::string name) const;

		bool loadTexture(const std::string name, const std::string path);
		bool isLoadedTexture(const std::string name);
		sf::Texture *getTexture(const std::string name);

		Entity cloneEntity(const Entity entityToClone);

	private:

		void checkSignatureLoad() const;

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;
		SignatureLoader m_signatureLoader;
		TextureKeeper m_textureKeeper;

		bool m_signaturesAreLoaded;
                              
};

}

#endif