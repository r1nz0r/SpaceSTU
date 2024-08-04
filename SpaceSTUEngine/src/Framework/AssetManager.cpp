#include "Framework/AssetManager.h"

namespace SSTU
{
	AssetManager& AssetManager::Instance()
	{
		static std::unique_ptr<AssetManager> sAssetManager { new AssetManager() };
		return *sAssetManager;
	}

	std::shared_ptr<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return LoadAsset(path, m_loadedTextures);
	}

	std::shared_ptr<sf::Font> AssetManager::LoadFont(const std::string& path)
	{		
		return LoadAsset(path, m_loadedFonts);
	}

	void AssetManager::Clean()
	{		
		CleanUniqueRef(m_loadedFonts);
		CleanUniqueRef(m_loadedTextures);
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		m_rootDirectory = directory;
	}

	AssetManager::AssetManager() : m_rootDirectory {}
	{}
}