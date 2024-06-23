#include "VFX/Explosion.h"
#include "Framework/MathUtility.h"
#include "VFX/Particle.h"
#include "Framework/World.h"

namespace SSTU
{
	Explosion::Explosion(int particleAmount,
		const sf::Vector2<sf::Time>& lifeTimeRange,
		const sf::Vector2f& sizeRange,
		const sf::Vector2f& speedRange,
		const sf::Color& color,
		const List<std::string>& particleImagePaths
	)
		: m_particlesAmount{particleAmount}
		, m_lifeTimeRange{lifeTimeRange}
		, m_sizeRange{sizeRange}
		, m_speedRange{speedRange}
		, m_color{color}
		, m_particleImagePaths{particleImagePaths}
	{}

	void Explosion::SpawnExplosion(World * world, const sf::Vector2f& location)
	{
		if (!world)
			return;

		for (int i = 0; i < m_particlesAmount; ++i)
		{
			int randomIndex = static_cast<int>(Math::RandomRange(0, m_particleImagePaths.size()));
			std::string particleImagePath = m_particleImagePaths[randomIndex];
			std::weak_ptr<Particle> particle = world->SpawnActor<Particle>(particleImagePath);

			particle.lock()->RandomLifeTime(m_lifeTimeRange.x.asSeconds(), m_lifeTimeRange.y.asSeconds());
			particle.lock()->SetLocation(location);
			particle.lock()->RandomSize(m_sizeRange.x, m_sizeRange.y);
			particle.lock()->RandomVelocity(m_speedRange.x, m_speedRange.y);
			particle.lock()->GetSprite().setColor(m_color);
		}
	}
}