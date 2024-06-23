#pragma once
#include "Framework/Core.h"
#include "SpaceShip/SpaceShip.h"

namespace SSTU
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owner, const std::string& texturePath, float collisionDamage = 200.0f);
		virtual void Tick(float deltaTime);
	private:
		float m_collisionDamage;
		virtual void OnBeginOverlap(Actor* actor) override;
	};
}