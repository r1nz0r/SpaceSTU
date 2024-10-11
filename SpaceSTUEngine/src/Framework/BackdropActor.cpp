#include "Framework/BackdropActor.h"
#include "Framework/World.h"
#include "Framework/Application.h"

namespace SSTU
{
	BackdropActor::BackdropActor(World* owner, const std::string& texture, const sf::Vector2f& velocity)
		: Actor(owner, texture)
		, m_velocity(velocity)
		, m_shift()
	{
		auto windowSize = owner->GetApplication()->GetWindowSize();
		GetSprite().setOrigin(0.f, 0.f);
		GetSprite().setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(windowSize.x, windowSize.y)));
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		m_shift.x += deltaTime * m_velocity.x;
		m_shift.y -= deltaTime * m_velocity.y;

		sf::IntRect currentRect = GetSprite().getTextureRect();
		currentRect.left = m_shift.x;
		currentRect.top = m_shift.y;

		GetSprite().setTextureRect(currentRect);
	}
}