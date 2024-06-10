#include "Framework/Actor.h"
#include "Framework/Core.h"
#include "Framework/AssetManager.h"
#include "Framework/MathUtility.h"

namespace SSTU
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: m_owner{ owner }
		, m_bBeganPlay{ false }
		, m_texture{}
		, m_sprite{}

	{}

	Actor::~Actor()
	{
		LOG("Actor destroyed!");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_bBeganPlay)
		{
			m_bBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingDestroy())
			return;

		Tick(deltaTime);
	}

	void Actor::BeginPlay()
	{
		//LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor Ticking");
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_texture = AssetManager::Instance().LoadTexture(texturePath);
		//assert(m_texture);
		if (!m_texture)
			return;

		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{m_texture->getSize()}});
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window) const
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_sprite);
	}

	void Actor::SetLocation(const sf::Vector2f& location)
	{
		m_sprite.setPosition(location);
	}

	void Actor::SetRotation(float rotation)
	{
		m_sprite.setRotation(rotation);
	}

	sf::Vector2f Actor::GetLocation() const
	{
		return m_sprite.getPosition();
	}

	float Actor::GetRotation() const
	{
		return m_sprite.getRotation();
	}

	void Actor::AddLocationOffset(const sf::Vector2f& offset)
	{
		SetLocation(GetLocation() + offset);
	}

	void Actor::AddRotationOffset(float offset)
	{
		SetRotation(GetRotation() + offset);
	}

	sf::Vector2f Actor::GetForwardVector() const
	{
		return Math::RotationToVector(GetRotation());
	}

	sf::Vector2f Actor::GetRightVector() const
	{
		return Math::RotationToVector(GetRotation() + 90.0f);
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bounds = m_sprite.getGlobalBounds();
		m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	}
}

