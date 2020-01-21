#ifndef GULG_ENGINE_HPP
#define GULG_ENGINE_HPP

<<<<<<< HEAD
#include <GL/glew.h>
#include <GL/gl.h>

#include "GulgEngine/GulgDeclarations.hpp"

=======
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025
#include "GulgEngine/EntityCreator.hpp"
#include "GulgEngine/EntitySignatureKeeper.hpp"
#include "GulgEngine/SignatureLoader.hpp"
#include "GulgEngine/ComponentKeeper.hpp"
<<<<<<< HEAD
#include "GulgEngine/ProgramKeeper.hpp"

#include "Components/Component.hpp"

=======
#include "GulgEngine/TextureKeeper.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

#include "Components/Component.hpp"



>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025
namespace Gg {

class GulgEngine {

	public:

		GulgEngine();

		bool loadSignatures(const std::string path);

		Entity getNewEntity();
		void deleteEntity(const Entity entity);

		void addComponentToEntity(const Entity entity, const std::string name, std::shared_ptr<Component::AbstractComponent> component);
		void deleteComponentToEntity(const Entity entity, const std::string name);
		bool entityHasComponent(const Entity entity, const std::string name);

		Signature getEntitySignature(const Entity entity) const;

		std::shared_ptr<Component::AbstractComponent> getComponent(const Entity entity, const std::string name) const;
		Signature getComponentSignature(const std::string name) const;

<<<<<<< HEAD
		bool loadProgram(const std::string vertexPath, const std::string fragmentPath, const std::string name);
		GLuint getProgram(const std::string name) const;

=======
		bool loadTexture(const std::string name, const std::string path);
		bool isLoadedTexture(const std::string name);
		sf::Texture *getTexture(const std::string name);
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025

		Entity cloneEntity(const Entity entityToClone);

	private:

		void checkSignatureLoad() const;

		EntityCreator m_entityCreator;
		EntitySignatureKeeper m_entitySignatureKeeper;
		ComponentKeeper m_componentKeeper;
		SignatureLoader m_signatureLoader;
<<<<<<< HEAD
		ProgramKeeper m_programKeeper;
=======
		TextureKeeper m_textureKeeper;
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025

		bool m_signaturesAreLoaded;
                              
};

}

#endif