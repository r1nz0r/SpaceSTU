#pragma once
#include "Enemy/EnemySpaceship.h"

namespace SSTU
{
	class BulletShooter;
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owner, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoBlue.png", float rotationSpeed = 40.f);

		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;

		std::unique_ptr<BulletShooter> m_shooter1;
		std::unique_ptr<BulletShooter> m_shooter2;
		std::unique_ptr<BulletShooter> m_shooter3;
		float m_rotationSpeed;
	};
}