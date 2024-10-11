#pragma once

#include "Enemy/EnemySpaceship.h"
#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace SSTU
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);
		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		float m_speed;
		float m_baseSpeed;
		float m_switchDistanceToEdge;
		void CheckMove();

		BulletShooter m_baseShooterLeft;
		BulletShooter m_baseShooterRight;

		ThreeWayShooter m_threeWayShooter;
		FrontalWiper m_frontalWiperLeft;
		FrontalWiper m_frontalWiperRight;

		BulletShooter m_finalStageShooterLeft;
		BulletShooter m_finalStageShooterRight;

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();
		void OnHealthChanged(float amt, float currentHealth, float maxHealth);

		void SetStage(int newStage);
		int m_stage;
	};
}