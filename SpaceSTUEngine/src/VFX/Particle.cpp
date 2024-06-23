#include "VFX/Particle.h"
#include "Framework/MathUtility.h"

namespace SSTU
{
	Particle::Particle(World* owner, const std::string& texturePath)
		: Actor(owner, texturePath)
		, m_velocity{}
		, m_lifeTime { sf::seconds(1.f)}
		, m_timer{}
	{}


	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (m_timer.getElapsedTime() > m_lifeTime)
		{
			Destroy();
		}

	}

	void Particle::RandomVelocity(float min, float max)
	{
		m_velocity = Math::RandomNormalizedVector() * Math::RandomRange(min, max);
	}

	void Particle::RandomSize(float min, float max)
	{
		float randScale = Math::RandomRange(min, max);
		GetSprite().setScale(randScale, randScale);
	}

	void Particle::RandomLifeTime(float min, float max)
	{
		m_lifeTime = sf::seconds(Math::RandomRange(min, max));
	}

	void Particle::Move(float deltaTime)
	{
		AddLocationOffset(m_velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		sf::Time elapsedTime = m_timer.getElapsedTime();
		float alpha = elapsedTime / m_lifeTime;

		sf::Color targetColor = sf::Color(255, 255, 255, 0);
		GetSprite().setColor(Math::LerpColor(GetSprite().getColor(), targetColor, alpha));

		sf::Vector2f targetScale = sf::Vector2f { 0,0 };
		GetSprite().setScale(Math::LerpVector(GetSprite().getScale(), targetScale, alpha));
	}
}