#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Framework/Core.h"
#include <string>

namespace SSTU
{
	class World;
	class Explosion
	{
	public:
		Explosion(int particleAmount = 20,
			const sf::Vector2<sf::Time>& lifeTimeRange = {sf::seconds(0.5f), sf::seconds(1.5f)},
			const sf::Vector2f& sizeRange = {2.0f, 4.0f},
			const sf::Vector2f& speedRange = {200.0f, 400.0f},
			const sf::Color& color = {255,128,0,255},
			const List<std::string>& particleImagePaths = 
			{
				"SpaceShooterRedux\\PNG\\Effects\\star1.png",
				"SpaceShooterRedux\\PNG\\Effects\\star2.png",
				"SpaceShooterRedux\\PNG\\Effects\\star3.png"
			}
		);

		void SpawnExplosion(World* world, const sf::Vector2f& location);

	private:
		int m_particlesAmount;
		sf::Vector2<sf::Time> m_lifeTimeRange;
		sf::Vector2f m_sizeRange;
		sf::Vector2f m_speedRange;
		sf::Color m_color;

		List<std::string> m_particleImagePaths;
	};
}