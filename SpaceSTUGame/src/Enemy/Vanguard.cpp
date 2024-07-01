#include "Enemy/Vanguard.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	Vanguard::Vanguard(World* owner, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship(owner, texturePath)
		, m_shooter { new BulletShooter{this, sf::seconds(1.f), {50.f, 0.f}} }
	{
		SetVelocity(velocity);
		SetRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		if (!m_shooter)
			return;

		m_shooter->Shoot();
	}
}