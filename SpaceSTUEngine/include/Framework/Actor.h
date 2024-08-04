#pragma once
#include "Framework/Object.h"
#include "SFML/Graphics.hpp"
#include "Framework/Delegate.h"

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
		const World* GetWorld() const { return m_ownerWorld; }
		World* GetWorld() { return m_ownerWorld; }
		void CenterPivot();
		bool IsOutOfWindow(float allowance = 10.0f) const;

		void SetEnablePhysics(bool bState);
		void UpdatePhysicsBodyTransform();
		virtual void OnBeginOverlap(Actor* other);
		virtual void OnEndOverlap(Actor* other);
		virtual void Destroy() override;

		static uint8_t GetNeutralTeamId() { return NEUTRAL_TEAM_ID; }
		uint8_t GetTeamId() const { return m_teamId; }
		void SetTeamId(uint8_t teamId) { m_teamId = teamId; }
		bool IsOtherHostile(Actor* other) const;
		virtual void ApplyDamage(float amount);

		sf::Sprite& GetSprite() { return m_sprite; }
		const sf::Sprite& GetSprite() const { return m_sprite; }

		Delegate<Actor*> onActorDestroyed;

	protected:
		World* m_ownerWorld;

	private:
		bool m_bBeganPlay;
		bool m_bPhysicsEnabled;

		sf::Sprite m_sprite;
		std::shared_ptr<sf::Texture> m_texture;
		b2Body* m_physicsBody;
		uint8_t m_teamId;
		const static uint8_t NEUTRAL_TEAM_ID = 255;

		void EnablePhysics();
		void DisablePhysics();

	};
}