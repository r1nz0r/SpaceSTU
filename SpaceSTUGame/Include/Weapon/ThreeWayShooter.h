#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(
			Actor* owner,
			const sf::Time& cooldownTime = sf::seconds(0.3f),
			const sf::Vector2f& localOffset = { 0.f, 0.f }
		);

		BulletShooter m_shooterLeft;
		BulletShooter m_shooterMid;
		BulletShooter m_shooterRight;

		BulletShooter m_topLevelShooterLeft;
		BulletShooter m_topLevelShooterRight;

		virtual void IncrementLevel(int amt) override;
		virtual void SetCurrentLevel(int level) override;
	private:
		virtual void ShootImpl();
	};
}