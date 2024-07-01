#include "Enemy/UFO.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	UFO::UFO(World* owner, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
		: EnemySpaceship { owner, texturePath },
		m_shooter1 { new BulletShooter{this, sf::seconds(.5f), sf::Vector2f{0.f,0.f}, -60}},
		m_shooter2 { new BulletShooter{this, sf::seconds(.5f), sf::Vector2f{0.f,0.f}, 60} },
		m_shooter3 { new BulletShooter{this, sf::seconds(.5f), sf::Vector2f{0.f,0.f}, 180.f} },
		m_rotationSpeed { rotationSpeed }
	{
		SetVelocity(velocity);
		SetRotation(90.f);
	}
	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
		AddRotationOffset(m_rotationSpeed * deltaTime);
	}
	void UFO::Shoot()
	{
		m_shooter1->Shoot();
		m_shooter2->Shoot();
		m_shooter3->Shoot();
	}
}