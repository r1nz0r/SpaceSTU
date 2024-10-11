#pragma once
#include "Framework/Actor.h"

namespace SSTU
{
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* owner,
			const std::string& texture,
			const sf::Vector2f& velocity = sf::Vector2f{0.f, 50.f}
		);
		virtual void Tick(float deltaTime) override;

	private:
		sf::Vector2f m_velocity;
		sf::Vector2f m_shift;
	};
}