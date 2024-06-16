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
		auto found = m_loadedTextures.find(path);
		if (found != m_loadedTextures.end())
			return found->second;

		auto newTexture = std::make_shared<sf::Texture>();		
		if (newTexture->loadFromFile(m_rootDirectory + path))
		{
			m_loadedTextures[path] = newTexture;
			return newTexture;
		}

		return nullptr;
	}

	void AssetManager::Clean()
	{		
		for (auto iter = m_loadedTextures.begin(); iter != m_loadedTextures.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning texture: %s", iter->first.c_str());
				iter = m_loadedTextures.erase(iter);			
			}
			else			
				++iter;			
		}
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		m_rootDirectory = directory;
	}

	AssetManager::AssetManager() : m_rootDirectory {}
	{}
}