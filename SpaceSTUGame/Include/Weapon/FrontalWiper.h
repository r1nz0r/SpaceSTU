#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(
			Actor* ownerActor,
			const sf::Time& cooldownTime = sf::seconds(0.3f),
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 60.f
		);

		virtual void IncrementLevel(int amt = 1) override;
		//virtual void SetCurrentLevel(int newLevel) override;
	private:
		virtual void ShootImpl() override;

		float mWidth;

		BulletShooter m_shooter1;
		BulletShooter m_shooter2;
		BulletShooter m_shooter3;
		BulletShooter m_shooter4;

		BulletShooter m_shooter5;
		BulletShooter m_shooter6;
	};
}