#include "Player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "Framework/MathUtility.h"
#include "Framework/Core.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace SSTU
{
	PlayerSpaceship::PlayerSpaceship(World* world, const std::string& path)
		: Spaceship(world, path)
		, m_moveInput()
		, m_speed(270.0f)
		, m_shooter(new BulletShooter(this, sf::seconds(0.1f), {50.f, 0.f}))
		, m_invulnerableTime(2.0f)
		, m_bIsInvulnerable(true)
		, m_invulnerableBlinkInterval(0.5f)
		, m_invulnerableBlinkTimer(0.f)
		, m_invulnerableBlinkDirection(1.0f)
	{
		SetTeamId(1);
	}
	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		ClampPosition();
		UpdateInvulnerableVisuals(deltaTime);
	}

	void PlayerSpaceship::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void PlayerSpaceship::Shoot()
	{
		if (!m_shooter)
			return;
		
		m_shooter->Shoot();
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Instance().SetTimer(GetWeakPtr(), &PlayerSpaceship::StopInvulnerable, m_invulnerableTime);
	}

	void PlayerSpaceship::SetShooter(std::unique_ptr<Shooter>&& newShooter)
	{
		if (m_shooter && typeid(*m_shooter.get()) == typeid(*newShooter.get()))
		{
			m_shooter->IncrementLevel();
			return;
		}

		m_shooter = std::move(newShooter);
	}

	void PlayerSpaceship::ApplyDamage(float amount)
	{
		if (!m_bIsInvulnerable)
			Spaceship::ApplyDamage(amount);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_moveInput.y = -1.0f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_moveInput.y = 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_moveInput.x = -1.0f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_moveInput.x = 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Shoot();

		Math::NormalizeVector(m_moveInput);
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_moveInput * m_speed);
		m_moveInput.x = m_moveInput.y = 0;
	}

	void PlayerSpaceship::ClampPosition()
	{
		if (!m_ownerWorld)
			return;

		if (!m_ownerWorld->GetApplication())
			return;

		sf::Vector2u windowSize = m_ownerWorld->GetApplication()->GetWindowSize();
		auto location = GetLocation();
		auto size = GetGlobalBounds();

		if (location.x - size.width / 2 <= 0.f)
			location.x = size.width / 2;
		else if (location.x + size.width / 2 >= windowSize.x)
			location.x = windowSize.x - size.width / 2;

		if (location.y - size.height / 2 <= 0.f)
			location.y = size.height / 2;
		else if (location.y + size.height / 2 >= windowSize.y)
			location.y = windowSize.y - size.height / 2;
		
		SetLocation(location);
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({ 255, 255, 255, 255 });
		m_bIsInvulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerableVisuals(float deltaTime)
	{
		if (!m_bIsInvulnerable)
			return;

		m_invulnerableBlinkTimer += deltaTime * m_invulnerableBlinkDirection;
		
		if (m_invulnerableBlinkTimer < 0 || m_invulnerableBlinkTimer > m_invulnerableBlinkInterval)
		{
			m_invulnerableBlinkDirection *= -1;
		}

		GetSprite().setColor(Math::LerpColor({ 255, 255, 255, 64 }, { 255, 255, 255, 128 }, m_invulnerableBlinkTimer / m_invulnerableBlinkInterval));
	}
}