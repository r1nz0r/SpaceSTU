#pragma once
#include "Framework/Actor.h"
#include "Gameplay/HealthComponent.h"

namespace SSTU
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owner, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f velocity);
		inline sf::Vector2f GetVelocity() const { return m_velocity; }
		virtual void Shoot() {};
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amount) override;

	private:
		virtual void OnHealthChanged(float amount, float health, float maxHealth);
		virtual void OnTakenDamage(float amount, float health, float maxHealth);
		virtual void Blow();
		void Blink();
		void UpdateBlink(float deltaTime);

		sf::Vector2f m_velocity;
		HealthComponent m_healthComponent;
		sf::Time m_blinkTime;
		sf::Time m_blinkDuration;
		sf::Color m_blinkColorOffset;
	};
}