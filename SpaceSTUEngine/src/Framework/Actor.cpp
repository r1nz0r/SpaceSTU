#include "Framework/Actor.h"
#include "Framework/Core.h"
#include "Framework/AssetManager.h"

namespace SSTU
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: m_owner { owner }
		, m_bBeganPlay { false }
		, m_texture {}
		, m_sprite {}

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
	}

	void Actor::Render(sf::RenderWindow& window) const
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_sprite);
	}
}

