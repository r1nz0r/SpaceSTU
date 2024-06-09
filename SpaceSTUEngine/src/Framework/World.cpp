#include "Framework/World.h"
#include "Framework/Actor.h"

namespace SSTU
{
	World::World(Application* ownerApp)
		: m_ownerApp {ownerApp}
		, m_bBeganPlay {false}
		, m_actors {}
		, m_pendingActors {}
	{}

	void World::Tick(float deltaTime)
	{
		//LOG("Ticking at framerate: %f", 1.0f / deltaTime);
	}

	void World::BeginPlay()
	{
		//LOG("Begin play!");
	}

	void World::TickInternal(float deltaTime)
	{
		for (auto& actor : m_pendingActors)
		{
			m_actors.push_back(actor);
			actor->BeginPlayInternal();
		}

		m_pendingActors.clear();

		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}

		Tick(deltaTime);
	}

	void World::BeginPlayInternal()
	{
		if (!m_bBeganPlay)
		{
			m_bBeganPlay = true;
			BeginPlay();
		}
	}
	void World::Render(sf::RenderWindow& window)
	{
		for (const auto& actor : m_actors)
		{
			actor->Render(window);
		}
	}
}

