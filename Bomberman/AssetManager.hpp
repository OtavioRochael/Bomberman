#pragma once

#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
private:
	std::map<std::string, sf::Texture> textures;

	static AssetManager* sInstance;
};

