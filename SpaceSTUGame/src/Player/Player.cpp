#include "Player/Player.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Player/PlayerSpaceship.h"
#include "Weapon/Bullet.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	Player::Player()
		: m_lifeCount { 3 }
		, m_score { 0 }
		, m_spaceship {}
	{}

	std::weak_ptr<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (m_lifeCount > 0)
		{
			--m_lifeCount;
			onLifeChanged.Notify(m_lifeCount);

			m_spaceship = world->SpawnActor<PlayerSpaceship>();
			auto windowSize = world->GetApplication()->GetWindowSize();
			m_spaceship.lock()->SetLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));
			m_spaceship.lock()->SetRotation(-90.f);			
		}
		else
		{
			m_spaceship = std::weak_ptr<PlayerSpaceship> {};
			onLifeExhausted.Notify();
		}

		return m_spaceship;
	}

	void Player::AddLifes(unsigned int count)
	{
		if (count > 0)
		{
			m_lifeCount += count;
			onLifeChanged.Notify(m_lifeCount);
		}
	}

	void Player::AddScore(unsigned int amt)
	{
		if (amt > 0)
		{
			m_score += amt;
			onScoreChanged.Notify(m_score);
		}
	}
}