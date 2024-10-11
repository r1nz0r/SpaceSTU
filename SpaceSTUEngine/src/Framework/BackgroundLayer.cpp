#include "Framework/BackgroundLayer.h"
#include "Framework/AssetManager.h"
#include "Framework/MathUtility.h"
#include "Framework/World.h"
#include "Framework/Application.h"

namespace SSTU
{
	BackgroundLayer::BackgroundLayer(
		World* owner,
		const List<std::string>& assetsPath,
		const sf::Vector2f& minVelocity,
		const sf::Vector2f& maxVelocity,
		float sizeMin,
		float sizeMax,
		int spritesCount,
		const sf::Color& tintColor
	)
		: Actor(owner)
		, m_minVelocity(minVelocity)
		, m_maxVelocity(maxVelocity)
		, m_sizeMin(sizeMin)
		, m_sizeMax(sizeMax)
		, m_spritesCount(spritesCount)
		, m_tintColor(tintColor)
	{
		SetEnablePhysics(false);
		SetAssets(assetsPath);
	}

	void BackgroundLayer::SetAssets(const List<std::string>& assetsPath)
	{
		for (const auto& asset : assetsPath)
		{
			std::shared_ptr<sf::Texture> newTexture = AssetManager::Instance().LoadTexture(asset);
			m_textures.push_back(newTexture);
		}

		RefreshSprites();
	}

	void BackgroundLayer::RefreshSprites()
	{
		m_sprites.clear();
		m_velocities.clear();

		for (int i = 0; i < m_spritesCount; ++i)
		{
			sf::Sprite newSprite {};
			SetRandomSpriteTexture(newSprite);
			SetRandomSpriteTransform(newSprite, true);
			m_sprites.push_back(newSprite);

			float velocityX = Math::RandomRange(m_minVelocity.x, m_maxVelocity.x);
			float velocityY = Math::RandomRange(m_minVelocity.y, m_maxVelocity.y);
			m_velocities.push_back(sf::Vector2f(velocityX, velocityY));
		}

		SetTintColor(m_tintColor);
	}

	void BackgroundLayer::SetRandomSpriteTexture(sf::Sprite& sprite)
	{
		if (!m_textures.empty())
		{
			std::shared_ptr<sf::Texture> pickedTexture = GetRandomTexture();
			sprite.setTexture(*(pickedTexture).get());
			sprite.setTextureRect(sf::IntRect(0, 0, (int)pickedTexture->getSize().x, (int)pickedTexture->getSize().y));
			sf::FloatRect bound = sprite.getGlobalBounds();
			sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
		}
	}

	void BackgroundLayer::SetRandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		SetRandomSpritePosition(sprite, randomY);
		SetRandomSpriteRotation(sprite);
		SetRandomSpriteSize(sprite);
	}

	void BackgroundLayer::SetRandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto& windowSize = GetWorld()->GetApplication()->GetWindowSize();
		auto& bounds = sprite.getGlobalBounds();

		float posX = Math::RandomRange(0, windowSize.x);
		float posY = randomY ? Math::RandomRange(0, windowSize.y) : -bounds.height;

		sprite.setPosition(sf::Vector2f(posX, posY));
	}

	void BackgroundLayer::SetRandomSpriteRotation(sf::Sprite & sprite)
	{
		sprite.setRotation(Math::RandomRange(0, 360.f));
	}

	void BackgroundLayer::SetRandomSpriteSize(sf::Sprite & sprite)
	{
		float size = Math::RandomRange(m_sizeMin, m_sizeMax);
		sprite.setScale(size, size);
	}

	bool BackgroundLayer::IsSpriteOutScreen(const sf::Sprite& sprite)
	{
		auto& bounds = sprite.getGlobalBounds();
		auto& windowSize = GetWorld()->GetApplication()->GetWindowSize();
		auto& spritePosition = sprite.getPosition();

		if (spritePosition.x < -bounds.width || spritePosition.x > windowSize.x + bounds.width)
			return true;
		if (spritePosition.y < -bounds.height / 2.f || spritePosition.y > windowSize.y + (bounds.height / 2.f))
			return true;

		return false;
	}

	void BackgroundLayer::SetTintColor(const sf::Color color)
	{
		m_tintColor = color;

		for (auto& sprite : m_sprites)
			sprite.setColor(color);
	}

	void BackgroundLayer::SetSpritesCount(int newCount)
	{
		m_spritesCount = newCount;
		RefreshSprites();
	}

	void BackgroundLayer::SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		m_minVelocity = min;
		m_maxVelocity = max;

		for (int i = 0; i < m_velocities.size(); ++i)
		{
			float velocityX = Math::RandomRange(m_minVelocity.x, m_maxVelocity.x);
			float velocityY = Math::RandomRange(m_minVelocity.y, m_maxVelocity.y);
			m_velocities[i] = sf::Vector2f(velocityX, velocityY);
		}
	}

	void BackgroundLayer::SetSizes(float min, float max)
	{
		m_sizeMin = min;
		m_sizeMax = max;

		for (int i = 0; i < m_sprites.size(); ++i)
		{
			SetRandomSpriteSize(m_sprites[i]);
		}
	}

	void BackgroundLayer::Render(sf::RenderWindow& window) const
	{
		Actor::Render(window);

		for (const auto& sprite : m_sprites)
			window.draw(sprite);
	}

	void BackgroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		for (int i = 0; i < m_sprites.size(); ++i)
		{
			sf::Sprite& sprite = m_sprites[i];
			sf::Vector2f& velocity = m_velocities[i];

			sprite.setPosition(sprite.getPosition() + velocity * deltaTime);
			
			if (IsSpriteOutScreen(sprite))
			{
				SetRandomSpriteTexture(sprite);
				SetRandomSpriteTransform(sprite);
				float velX = Math::RandomRange(m_minVelocity.x, m_maxVelocity.x);
				float velY = Math::RandomRange(m_minVelocity.y, m_maxVelocity.y);
				m_velocities[i] = sf::Vector2f { velX, velY };
			}
		}
	}

	std::shared_ptr<sf::Texture> BackgroundLayer::GetRandomTexture() const
	{
		int randomPickIndex = static_cast<int>(Math::RandomRange(0, m_textures.size()));
		return m_textures[randomPickIndex];
	}
}