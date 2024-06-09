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
		std::shared_ptr<sf::Texture> LoadTexture(const std::string& path);
		void Clean();
	protected:
		AssetManager() = default;
	private:
		Dictionary<std::string, std::shared_ptr<sf::Texture>> m_loadedTextures;
	};
}