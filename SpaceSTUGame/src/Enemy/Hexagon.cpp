#include "Enemy/Hexagon.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	Hexagon::Hexagon(World* owner, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owner, texturePath},
		m_shooter1{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{20.f, 50.f}, 30.f} },
		m_shooter2{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{20.f, -50.f}, -30.f} },
		m_shooter3{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{50.f, 0.0f}} },
		m_shooter4{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{-50.f, 0.0f}, -180.f} },
		m_shooter5{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{-20.f, 50.0f}, 120.f} },
		m_shooter6{ new BulletShooter{this, sf::seconds(1.f), sf::Vector2f{-20.f, -50.0f},-120.f} }
	{
		SetVelocity(velocity);
		SetRotation(90.f);
	}
	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
	void Hexagon::Shoot()
	{
		m_shooter1->Shoot();
		m_shooter2->Shoot();
		m_shooter3->Shoot();
		m_shooter4->Shoot();
		m_shooter5->Shoot();
		m_shooter6->Shoot();
	}
}