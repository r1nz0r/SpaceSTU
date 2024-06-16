#pragma once
#include "Framework/Core.h"
#include "SFML/Graphics.hpp"

namespace SSTU
{
	class AssetManager
	{
	public:
		static AssetManager& Instance();
		AssetManager(const AssetManager& other) = delete;
		AssetManager(AssetManager&& other) noexcept = delete;
		AssetManager& operator=(const AssetManager& other) = delete;
		AssetManager& operator=(AssetManager&& other) noexcept = delete;

		// Loads texture from user relative path
		std::shared_ptr<sf::Texture> LoadTexture(const std::string& path);

		// Check for texture is not in use anymore and delete if it is.
		void Clean();
		void SetAssetRootDirectory(const std::string& directory);
	protected:
		AssetManager();
	private:
		Dictionary<std::string, std::shared_ptr<sf::Texture>> m_loadedTextures;
		std::string m_rootDirectory;
	};
}