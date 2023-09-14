#include "AssetManager.hpp"
#include <assert.h>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
	auto& textureMap = sInstance->textures;

	auto pairFound = textureMap.find(filename);

	if (pairFound != textureMap.end()) {
		return pairFound->second;
	}
	else {
		auto& texture = textureMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}
