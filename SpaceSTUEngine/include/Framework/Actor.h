#pragma once
#include "Framework/Object.h"
#include "SFML/Graphics.hpp"

namespace SSTU
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owner, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window) const;
		void SetLocation(const sf::Vector2f& location);
		void SetRotation(float rotation); // Rotation in degrees;
		sf::Vector2f GetLocation() const;
		float GetRotation() const;
		void AddLocationOffset(const sf::Vector2f& offset);
		void AddRotationOffset(float offset);
		sf::Vector2f GetForwardVector() const;
		sf::Vector2f GetRightVector() const;
		void CenterPivot();

	private:
		World* m_owner;
		bool m_bBeganPlay;

		sf::Sprite m_sprite;
		std::shared_ptr<sf::Texture> m_texture;
	};
}