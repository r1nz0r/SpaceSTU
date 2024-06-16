#pragma once
#include "Framework/Object.h"
#include "SFML/Graphics.hpp"

class b2Body;

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
		sf::Vector2f GetLocation() const;	

		// Rotation in degrees;
		void SetRotation(float rotation); 
		// Returns rotation in degrees
		float GetRotation() const;		

		void AddLocationOffset(const sf::Vector2f& offset);
		void AddRotationOffset(float offset);
		sf::Vector2f GetForwardVector() const;
		sf::Vector2f GetRightVector() const;
		sf::FloatRect GetGlobalBounds() const { return m_sprite.getGlobalBounds(); }
		World* GetWorld() const { return m_ownerWorld; }
		void CenterPivot();
		bool IsOutOfWindow() const;

		void SetEnablephysics(bool bState);
		void UpdatePhysicsBodyTransform();
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		virtual void Destroy() override;

	protected:
		World* m_ownerWorld;

	private:
		bool m_bBeganPlay;
		bool m_bPhysicsEnabled;

		sf::Sprite m_sprite;
		std::shared_ptr<sf::Texture> m_texture;
		b2Body* m_physicsBody;

		void EnablePhysics();
		void DisablePhysics();

	};
}