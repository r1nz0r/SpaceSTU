#include "Enemy/TwinBlade.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	TwinBlade::TwinBlade(World* owner, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship(owner, texturePath)
		, m_shooterLeft {new BulletShooter{this, sf::seconds(1.f), {50.f, -20.f}}}
		, m_shooterRight{new BulletShooter{this, sf::seconds(1.f), {50.f, 20.f}}}
	{
		SetVelocity(velocity);
		SetRotation(90.f);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void TwinBlade::Shoot()
	{
		m_shooterLeft->Shoot();
		m_shooterRight->Shoot();
	}
}