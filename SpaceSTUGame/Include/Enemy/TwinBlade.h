#pragma once
#include "Enemy/EnemySpaceship.h"

namespace SSTU
{
	class BulletShooter;
	class TwinBlade : public EnemySpaceship
	{
	public:
		TwinBlade(
			World* owner,
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png",
			const sf::Vector2f& velocity = { 0.f, 125.f }
		);

		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

	private:
		std::unique_ptr<BulletShooter> m_shooterLeft;
		std::unique_ptr<BulletShooter> m_shooterRight;
	};
}