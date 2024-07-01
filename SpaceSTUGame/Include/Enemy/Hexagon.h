#pragma once
#include "Enemy/EnemySpaceship.h"

namespace SSTU
{
	class BulletShooter;
	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* owner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = sf::Vector2f { 0.f, 100.f });

		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;

		std::unique_ptr<BulletShooter> m_shooter1;
		std::unique_ptr<BulletShooter> m_shooter2;
		std::unique_ptr<BulletShooter> m_shooter3;
		std::unique_ptr<BulletShooter> m_shooter4;
		std::unique_ptr<BulletShooter> m_shooter5;
		std::unique_ptr<BulletShooter> m_shooter6;
	};
}