#pragma once
#include "SpaceShip/SpaceShip.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class Shooter;
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
		void SetShooter(std::unique_ptr<Shooter>&& newShooter);
		virtual void ApplyDamage(float amount) override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void ClampPosition();
		void StopInvulnerable();
		void UpdateInvulnerableVisuals(float deltaTime);

		sf::Vector2f m_moveInput;
		float m_speed;

		std::unique_ptr<Shooter> m_shooter;

		float m_invulnerableTime;
		TimerHandler m_invulnerableTimerHandler;
		bool m_bIsInvulnerable;
		float m_invulnerableBlinkInterval;
		float m_invulnerableBlinkTimer;
		float m_invulnerableBlinkDirection;
	};
}