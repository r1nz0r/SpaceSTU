#include "Weapon/BulletShooter.h"
#include "Framework/Core.h"
#include "Weapon/Bullet.h"
#include "Framework/World.h"

namespace SSTU
{
	BulletShooter::BulletShooter(
		Actor* owner,
		const sf::Time& cooldown,
		sf::Vector2f localPositionOffset,
		float localRotationOffset,
		const std::string& bulletTexturePath
	)
		: Shooter(owner)
		, m_cooldownClock()
		, m_cooldownTime(cooldown)
		, m_localPositionOffset(localPositionOffset)
		, m_localRotationOffset(localRotationOffset)
		, m_bulletTexturePath(bulletTexturePath)
	{}

	bool BulletShooter::IsOnCooldown() const
	{
		if (m_cooldownClock.getElapsedTime() >= sf::seconds(m_cooldownTime.asSeconds() / GetCurrentLevel()))
		{
			return false;
		}

		return true;
	}

	void BulletShooter::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);
	}

	void BulletShooter::ShootImpl()
	{
		m_cooldownClock.restart();
		std::weak_ptr<Bullet> newBullet = 
			GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), m_bulletTexturePath);

		sf::Vector2f ownersForwardDirection = GetOwner()->GetForwardVector();
		sf::Vector2f ownersRightDirection = GetOwner()->GetRightVector();

		auto location = GetOwner()->GetLocation() + 
			ownersForwardDirection * m_localPositionOffset.x + 
			ownersRightDirection * m_localPositionOffset.y;
		newBullet.lock()->SetLocation(location);
		newBullet.lock()->SetRotation(GetOwner()->GetRotation() + m_localRotationOffset);
	}
}