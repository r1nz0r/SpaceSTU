#include "Weapon/Shooter.h"

namespace SSTU
{
	Shooter::Shooter(Actor* owner)
		: m_owner(owner)
		, m_currentLevel{1}
		, m_maxLevel{4}
	{}

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImpl();
		}
	}

	void Shooter::IncrementLevel(int amount)
	{
		if (m_currentLevel == m_maxLevel)
			return;

		++m_currentLevel;
	}

	void Shooter::SetCurrentLevel(int level)
	{
		m_currentLevel = level;
	}
}