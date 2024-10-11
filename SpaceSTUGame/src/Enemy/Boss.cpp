#include "Enemy/Boss.h"
#include "Gameplay/HealthComponent.h"
#include "Framework/World.h"
#include "Framework/Application.h"

namespace SSTU
{
	Boss::Boss(World* world)
		: EnemySpaceship { world, "SpaceShooterRedux/PNG/Enemies/boss.png" }
		, m_speed(100.f)
		, m_baseSpeed(100.f)
		, m_switchDistanceToEdge(100.f)
		, m_baseShooterLeft(this, sf::seconds(1.f), {50.f, -50.f})
		, m_baseShooterRight(this, sf::seconds(1.f), {50.f, 50.f})
		, m_threeWayShooter(this, sf::seconds(4.f), {100.f, 0.f})
		, m_frontalWiperLeft(this, sf::seconds(5.f), {80.f, -100})
		, m_frontalWiperRight(this, sf::seconds(5.f), {80.f, 100})
		, m_finalStageShooterLeft(this, sf::seconds(0.3f), {50, -150.f})
		, m_finalStageShooterRight(this, sf::seconds(0.3f), {50, 150.f})
		, m_stage(1)
	{
		SetRotation(90.f);
		SetVelocity({ m_speed, 0.f });
		SetRewardSpawnWeight(0.f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootFrontalWipers();
		ShootThreeWayShooter();

		if (m_stage == 4)
		{
			m_finalStageShooterLeft.Shoot();
			m_finalStageShooterRight.Shoot();
		}

		CheckMove();
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();
		HealthComponent& healthComp = GetHealthComponent();
		healthComp.SetInitialHealth(3000.f, 3000.f);
		healthComp.onHealthChanged.BindAction(GetWeakPtr(), &Boss::OnHealthChanged);
	}

	void Boss::CheckMove()
	{
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();

		if (GetLocation().x > windowSize.x - m_switchDistanceToEdge)		
			SetVelocity({ -m_speed, 0.f });		
		else if (GetLocation().x < m_switchDistanceToEdge)		
			SetVelocity({ m_speed, 0.f });		
	}

	void Boss::ShootBaseShooters()
	{
		m_baseShooterLeft.Shoot();
		m_baseShooterRight.Shoot();
	}

	void Boss::ShootThreeWayShooter()
	{
		m_threeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		m_frontalWiperLeft.Shoot();
		m_frontalWiperRight.Shoot();
	}

	void Boss::OnHealthChanged(float amt, float currentHealth, float maxHealth)
	{
		float percentLeft = currentHealth / maxHealth;

		if (percentLeft < 0.7 && percentLeft > 0.5)		
			SetStage(2);		
		else if (percentLeft < 0.5 && percentLeft > 0.3)		
			SetStage(3);		
		else if (percentLeft < 0.3)		
			SetStage(4);		
	}

	void Boss::SetStage(int newStage)
	{
		m_stage = newStage;
		m_baseShooterLeft.SetCurrentLevel(m_stage);
		m_baseShooterRight.SetCurrentLevel(m_stage);
		m_frontalWiperLeft.SetCurrentLevel(m_stage);
		m_frontalWiperRight.SetCurrentLevel(m_stage);
		m_threeWayShooter.SetCurrentLevel(m_stage);
		m_speed = m_stage * m_baseSpeed;
	}
}