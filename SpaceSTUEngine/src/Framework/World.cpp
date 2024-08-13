#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Gameplay/GameStage.h"
#include "Widgets/HUD.h"
#include "Framework/Application.h"

namespace SSTU
{
	World::World(Application* ownerApp)
		: m_ownerApp { ownerApp }
		, m_bBeganPlay { false }
		, m_actors {}
		, m_pendingActors {}
		, m_currentStage{m_gameStages.end()}
	{}

	void World::Clean()
	{
		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{
			// We need to remove all actors wich were marked for deletion in prev frame.
			if (iter->get()->IsPendingDestroy())
				iter = m_actors.erase(iter);
			else
				++iter;
		}
	}

	void World::AddStage(const std::shared_ptr<GameStage>& newStage)
	{
		m_gameStages.push_back(newStage);
	}

	bool World::DispatchEvent(const sf::Event& event)
	{
		if (m_HUD)
		{
			return m_HUD->HandleEvent(event);
		}

		return false;
	}

	void World::Tick(float deltaTime)
	{
		//LOG("Ticking at framerate: %f", 1.0f / deltaTime);
	}

	void World::BeginPlay()
	{
		//LOG("Begin play!");
	}

	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (!m_HUD)
			return;

		m_HUD->Draw(window);
	}

	void World::InitGameStages()
	{}

	void World::OnAllGameStagesFinished()
	{
		LOG("All stages finished!");
	}

	void World::SetNextGameStage()
	{
		m_currentStage = m_gameStages.erase(m_currentStage);

		if (m_currentStage != m_gameStages.end())
		{
			m_currentStage->get()->onStageFinished.BindAction(GetWeakPtr(), &World::SetNextGameStage);
			m_currentStage->get()->Start();
		}
		else
		{
			OnAllGameStagesFinished();
		}
	}

	void World::StartStages()
	{
		m_currentStage = m_gameStages.begin();

		if (m_currentStage == m_gameStages.end())
			return;

		m_currentStage->get()->onStageFinished.BindAction(GetWeakPtr(), &World::SetNextGameStage);
		m_currentStage->get()->Start();
	}

	void World::TickInternal(float deltaTime)
	{
		// We need to spawn actors which were added in previous tick to the game.
		for (auto& actor : m_pendingActors)
		{
			m_actors.push_back(actor);
			actor->BeginPlayInternal();
		}

		m_pendingActors.clear();

		for (auto iter = m_actors.begin(); iter != m_actors.end(); ++iter)		
			iter->get()->TickInternal(deltaTime);			

		if (m_currentStage != m_gameStages.end())
			m_currentStage->get()->Tick(deltaTime);

		Tick(deltaTime);

		if (m_HUD)
		{
			if (!m_HUD->HasInit())
				m_HUD->NativeInit(m_ownerApp->GetWindow());

			m_HUD->Tick(deltaTime);
		}
	}

	void World::BeginPlayInternal()
	{
		if (!m_bBeganPlay)
		{
			m_bBeganPlay = true;
			InitGameStages();
			StartStages();
			BeginPlay();
		}
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (const auto& actor : m_actors)
		{
			actor->Render(window);
		}

		RenderHUD(window);
	}
}

