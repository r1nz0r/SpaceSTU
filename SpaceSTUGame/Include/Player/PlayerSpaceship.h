#pragma once
#include "SpaceShip/SpaceShip.h"

namespace SSTU
{
	class BulletShooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(
			World* owner,
			const std::string& path = R"(SpaceShooterRedux/PNG/playerShip2_red.png)"
		);

		virtual void Tick(float deltaTime) override;
		void SetSpeed(float speed);
		float GetSpeed() const { return m_speed; }
		virtual void Shoot() override;
		virtual void BeginPlay() override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void ClampPosition();

		sf::Vector2f m_moveInput;
		float m_speed;

		std::unique_ptr<BulletShooter> m_shooter;
	};
}