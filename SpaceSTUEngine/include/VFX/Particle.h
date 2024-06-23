#pragma once
#include "Framework/Actor.h"

namespace SSTU
{
	class Particle : public Actor
	{
	public:
		Particle(World* owner, const std::string& texturePath);
		virtual void Tick(float deltaTime) override;

		void RandomVelocity(float min, float max);
		void RandomSize(float min, float max);
		void RandomLifeTime(float min, float max);

	private:
		void Move(float deltaTime);
		void Fade(float deltaTime);

		sf::Vector2f m_velocity;
		sf::Time m_lifeTime;
		sf::Clock m_timer;
	};
}