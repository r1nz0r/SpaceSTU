#include "Spaceship/SpaceShip.h"

namespace SSTU
{
	Spaceship::Spaceship(World* owner, const std::string& texturePath)
		: Actor{owner, texturePath}
		, m_velocity {}
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
	}
}