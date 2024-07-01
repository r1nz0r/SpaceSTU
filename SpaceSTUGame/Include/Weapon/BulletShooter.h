#pragma once
#include "Weapon/Shooter.h"
#include "SFML/System.hpp"

namespace SSTU
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(
			Actor* owner,
			const sf::Time& cooldown = sf::seconds(1.0f),
			sf::Vector2f localPositionOffset = {0.f, 0.f},
			float localRotationOffset = 0,
			const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
		);
		virtual bool IsOnCooldown() const override;

		void SetBulletTexturePath(const std::string& newBulletTexture) { m_bulletTexturePath = newBulletTexture; }
		virtual void IncrementLevel(int amount = 1) override;

	private:
		virtual void ShootImpl() override;

		sf::Clock m_cooldownClock;
		sf::Time m_cooldownTime;

		sf::Vector2f m_localPositionOffset;
		float m_localRotationOffset;

		std::string m_bulletTexturePath;
	};
}
