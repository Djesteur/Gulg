#include "GulgEngine/TextureKeeper.hpp"	

namespace Gg {

TextureKeeper::TextureKeeper() {}

bool TextureKeeper::loadTexture(const std::string name, const std::string path) {

	if(!isLoadedTexture(name)) {

		m_textures.insert(std::make_pair(name, sf::Texture{}));
		if(!m_textures[name].loadFromFile(path)) {

			m_textures.erase(name);
			return false;
		}
	}

	return true;
}

bool TextureKeeper::isLoadedTexture(const std::string name) {

	if(m_textures.find(name) != m_textures.end()) { return true; }
	return false;
}

sf::Texture *TextureKeeper::getTexture(const std::string name) {

	if(isLoadedTexture(name)) { return &(m_textures[name]); }

	throw std::runtime_error("Gulg error: asked for texture \"" + name + "\", which isn't loaded.");
	return nullptr;
}

}