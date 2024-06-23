#include "Weapon/BulletShooter.h"
#include "Framework/Core.h"
#include "Weapon/Bullet.h"
#include "Framework/World.h"

namespace SSTU
{
	BulletShooter::BulletShooter(Actor* owner, const sf::Time& cooldown)
		: Shooter(owner)
		, m_cooldownClock()
		, m_cooldownTime(cooldown)
	{}

	bool BulletShooter::IsOnCooldown() const
	{
		if (m_cooldownClock.getElapsedTime() >= m_cooldownTime)
		{
			return false;
		}

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		m_cooldownClock.restart();
		std::weak_ptr<Bullet> newBullet = 
			GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");

		auto location = GetOwner()->GetLocation() + GetOwner()->GetForwardVector() * 50.0f;
		newBullet.lock()->SetLocation(location);
		newBullet.lock()->SetRotation(GetOwner()->GetRotation());
	}
}