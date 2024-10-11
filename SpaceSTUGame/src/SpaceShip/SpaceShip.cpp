#include "Spaceship/SpaceShip.h"
#include "Framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace SSTU
{
	Spaceship::Spaceship(World* owner, const std::string& texturePath)
		: Actor{owner, texturePath}
		, m_velocity {}
		, m_healthComponent{100.f, 100.f}
		, m_blinkTime { sf::seconds(0.f) }
		, m_blinkDuration{sf::seconds(0.2f)}
		, m_blinkColorOffset{255, 0, 0}
	{}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f velocity)
	{
		m_velocity = velocity;
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		auto ptr = weak_from_this();
		m_healthComponent.onHealthChanged.BindAction(ptr, &Spaceship::OnHealthChanged);
		m_healthComponent.onTakenDamage.BindAction(ptr, &Spaceship::OnTakenDamage);
		m_healthComponent.onHealthEmpty.BindAction(ptr, &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amount)
	{
		m_healthComponent.ChangeHealth(-amount);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{}

	void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Explosion* expl = new Explosion();
		expl->SpawnExplosion(GetWorld(), GetLocation());
		OnBlow();
		Destroy();
		delete expl;
	}

	void Spaceship::OnBlow()
	{
	}

	void Spaceship::Blink()
	{
		if (m_blinkTime == sf::Time::Zero)
			m_blinkTime = m_blinkDuration;
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (m_blinkTime > sf::Time::Zero)
		{
			m_blinkTime -= sf::seconds(deltaTime);
			m_blinkTime = m_blinkTime > sf::seconds(0) ? m_blinkTime : sf::seconds(0);

			GetSprite().setColor(Math::LerpColor(sf::Color::White, m_blinkColorOffset, m_blinkTime.asSeconds() / m_blinkDuration.asSeconds()));
		}
	}
}