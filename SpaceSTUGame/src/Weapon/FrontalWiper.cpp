#include "Weapon/FrontalWiper.h"

namespace SSTU
{
	FrontalWiper::FrontalWiper(
		Actor* ownerActor,
		const sf::Time& cooldownTime,
		const sf::Vector2f& localOffset,
		float width
	)
		: Shooter { ownerActor }
		, mWidth { width }
		, m_shooter1 { ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
		, m_shooter2 { ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" }
		, m_shooter3 { ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" }
		, m_shooter4 { ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
		, m_shooter5 { ownerActor, cooldownTime / 1.5f, {localOffset.x, localOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
		, m_shooter6 { ownerActor, cooldownTime / 1.5f, {localOffset.x, localOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{

	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		m_shooter1.IncrementLevel(amt);
		m_shooter2.IncrementLevel(amt);
		m_shooter3.IncrementLevel(amt);
		m_shooter4.IncrementLevel(amt);
		m_shooter5.IncrementLevel(amt);
		m_shooter6.IncrementLevel(amt);
	}

	void FrontalWiper::SetCurrentLevel(int newLevel)
	{
		Shooter::SetCurrentLevel(newLevel);
		m_shooter1.SetCurrentLevel(newLevel);
		m_shooter2.SetCurrentLevel(newLevel);
		m_shooter3.SetCurrentLevel(newLevel);
		m_shooter4.SetCurrentLevel(newLevel);
		m_shooter5.SetCurrentLevel(newLevel);
		m_shooter6.SetCurrentLevel(newLevel);
	}

	void FrontalWiper::ShootImpl()
	{
		m_shooter1.Shoot();
		m_shooter2.Shoot();
		m_shooter3.Shoot();
		m_shooter4.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_shooter5.Shoot();
			m_shooter6.Shoot();
		}
	}
}