#pragma once
#include "Weapon/Shooter.h"
#include "SFML/System.hpp"

namespace SSTU
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, const sf::Time& cooldown = sf::seconds(1.f));
		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootImpl() override;

		sf::Clock m_cooldownClock;
		sf::Time m_cooldownTime;
	};
}
