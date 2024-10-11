#pragma once
#include "Framework/Actor.h"

namespace SSTU
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(
			World* owner,
			const List<std::string>& assetsPath = {},
			const sf::Vector2f& minVelocity = sf::Vector2f(0.f, 50.f),
			const sf::Vector2f& maxVelocity = sf::Vector2f(0.f, 200.f),
			float sizeMin = 1.f,
			float sizeMax = 2.f,
			int spritesCount = 20,
			const sf::Color& tintColor = sf::Color(180, 180, 200, 225)
		);
		void SetAssets(const List<std::string>& assetsPath);
		void SetTintColor(const sf::Color color);
		void SetSpritesCount(int newCount);
		void SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max);
		void SetSizes(float min, float max);

		virtual void Render(sf::RenderWindow& window) const override;
		virtual void Tick(float deltaTime) override;

	private:
		void RefreshSprites();
		void SetRandomSpriteTexture(sf::Sprite& sprite);
		void SetRandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void SetRandomSpritePosition(sf::Sprite& sprite, bool randomY = false);
		void SetRandomSpriteRotation(sf::Sprite& sprite);
		void SetRandomSpriteSize(sf::Sprite& sprite);
		bool IsSpriteOutScreen(const sf::Sprite& sprite);

		std::shared_ptr<sf::Texture> GetRandomTexture() const;

		sf::Vector2f m_minVelocity;
		sf::Vector2f m_maxVelocity;
		
		float m_sizeMin;
		float m_sizeMax;

		int m_spritesCount;
		sf::Color m_tintColor;

		List<std::shared_ptr<sf::Texture>> m_textures;
		List<sf::Sprite> m_sprites;
		List<sf::Vector2f> m_velocities;
	};
}