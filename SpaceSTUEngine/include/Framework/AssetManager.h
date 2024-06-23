#pragma once
#include "Framework/Core.h"
#include "SFML/Graphics.hpp"
#include "Framework/NonCopyable.h"

namespace SSTU
{
	class AssetManager : private NonCopyable
	{
	public:
		static AssetManager& Instance();

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