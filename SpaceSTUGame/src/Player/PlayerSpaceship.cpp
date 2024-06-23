#include "Player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "Framework/MathUtility.h"
#include "Framework/Core.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	PlayerSpaceship::PlayerSpaceship(World* world, const std::string& path)
		: Spaceship(world, path)
		, m_moveInput()
		, m_speed(200.0f)
		, m_shooter(new BulletShooter(this, sf::seconds(0.2f)))
	{
		SetTeamId(1);
	}
	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		ClampPosition();
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
}