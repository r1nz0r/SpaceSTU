#include "Spaceship/SpaceShip.h"

namespace SSTU
{
	Spaceship::Spaceship(World* owner, const std::string& texturePath)
		: Actor{owner, texturePath}
		, m_velocity {}
		, m_healthComponent{100.f, 100.f}
	{}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f velocity)
	{
		m_velocity = velocity;
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablephysics(true);
		auto ptr = GetWeakPtr();
		m_healthComponent.onHealthChanged.BindAction(ptr, &Spaceship::OnHealthChanged);
		m_healthComponent.onHealthChanged.Notify(11, 89, 100);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
		LOG("Health changed by: %f, and is now: %f/%f", amount, health, maxHealth);
	}
}