#pragma once
#include "Framework/Actor.h"

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
		sf::Vector2f m_velocity;
	};
}