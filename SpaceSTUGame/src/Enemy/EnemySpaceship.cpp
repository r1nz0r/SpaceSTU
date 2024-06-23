#include "Enemy/EnemySpaceship.h"

namespace SSTU
{
	EnemySpaceship::EnemySpaceship(
		World* owner,
		const std::string& texturePath,
		float collisionDamage
	)	: Spaceship(owner, texturePath)
		, m_collisionDamage {collisionDamage}
	{
		SetTeamId(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsOutOfWindow(std::max(GetGlobalBounds().width, GetGlobalBounds().height)))
			Destroy();
	}

	void EnemySpaceship::OnBeginOverlap(Actor * other)
	{
		Spaceship::OnBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(m_collisionDamage);
		}
	}
}