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

	private:
		void OnHealthChanged(float amount, float health, float maxHealth);
		sf::Vector2f m_velocity;
		HealthComponent m_healthComponent;
	};
}