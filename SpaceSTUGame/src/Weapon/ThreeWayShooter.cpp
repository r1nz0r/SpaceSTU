#include "Weapon/ThreeWayShooter.h"

namespace SSTU
{
	ThreeWayShooter::ThreeWayShooter(
		Actor* owner,
		const sf::Time& cooldownTime,
		const sf::Vector2f& localOffset)
		: Shooter { owner },
		m_shooterLeft { owner, cooldownTime, localOffset + sf::Vector2f{10, -10}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		m_shooterMid { owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		m_shooterRight { owner, cooldownTime, localOffset + sf::Vector2f{10, 10}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		m_topLevelShooterLeft { owner, cooldownTime, localOffset + sf::Vector2f{10, 10}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		m_topLevelShooterRight { owner, cooldownTime, localOffset + sf::Vector2f{10, -10}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		m_shooterLeft.IncrementLevel(amt);
		m_shooterMid.IncrementLevel(amt);
		m_shooterRight.IncrementLevel(amt);

		m_topLevelShooterLeft.IncrementLevel(amt);
		m_topLevelShooterRight.IncrementLevel(amt);
	}

	/*
	void ThreeWayShooter::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		m_shooterLeft.SetCurrentLevel(level);
		m_shooterMid.SetCurrentLevel(level);
		m_shooterRight.SetCurrentLevel(level);

		m_topLevelShooterLeft.SetCurrentLevel(level);
		m_topLevelShooterRight.SetCurrentLevel(level);
	}*/

	void ThreeWayShooter::ShootImpl()
	{
		m_shooterLeft.Shoot();
		m_shooterMid.Shoot();
		m_shooterRight.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_topLevelShooterLeft.Shoot();
			m_topLevelShooterRight.Shoot();
		}
	}
}