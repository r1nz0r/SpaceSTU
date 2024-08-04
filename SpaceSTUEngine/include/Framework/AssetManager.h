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
		std::shared_ptr<sf::Font> LoadFont(const std::string& path);
		// Check for texture is not in use anymore and delete if it is.
		void Clean();
		void SetAssetRootDirectory(const std::string& directory);
	protected:
		AssetManager();
	private:
		template<typename T>
		std::shared_ptr<T> LoadAsset(const std::string& path, Dictionary<std::string, std::shared_ptr<T>>& container);
		
		template<typename T>
		void CleanUniqueRef(Dictionary<std::string, std::shared_ptr<T>>& container);
		
		Dictionary<std::string, std::shared_ptr<sf::Texture>> m_loadedTextures;
		Dictionary<std::string, std::shared_ptr<sf::Font>> m_loadedFonts;
		std::string m_rootDirectory;
	};

	template<typename T>
	inline std::shared_ptr<T> AssetManager::LoadAsset(const std::string& path, Dictionary<std::string, std::shared_ptr<T>>& container)
	{
		auto found = container.find(path);

		if (found != container.end())
			return found->second;

		auto newAsset = std::make_shared<T>();

		if (newAsset->loadFromFile(m_rootDirectory + path))
		{
			container[path] = newAsset;
			return newAsset;
		}

		return nullptr;
	}

	template<typename T>
	inline void AssetManager::CleanUniqueRef(Dictionary<std::string, std::shared_ptr<T>>& container)
	{
		for (auto iter = container.begin(); iter != container.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning: %s", iter->first.c_str());
				iter = container.erase(iter);
			}
			else
				++iter;
		}
	}
}