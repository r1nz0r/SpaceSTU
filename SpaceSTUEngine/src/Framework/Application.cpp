#include "Framework/Application.h"
#include "Framework/Core.h"
#include "Framework/World.h"
#include "Framework/AssetManager.h"
#include "Framework/PhysicsSystem.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	Application::Application(
		uint32_t windowWidth,
		uint32_t windowHeight,
		const std::string& title,
		sf::Uint32 style)
		: m_window { sf::VideoMode(windowWidth, windowHeight), title, style }
		, m_targetFrameRate { 60.0f }
		, m_tickClock {}
		, m_currentWorld { nullptr }
		, m_cleanCycleClock {}
		, m_cleanCycleInterval { sf::seconds(2.0f) }
	{}

	void Application::Run()
	{
		sf::Time accumulatedTime {};

		while (m_window.isOpen())
		{
			sf::Event event;

			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed())
				{
					Quit();
				}
				else
				{
					DispatchEvent(event);
				}
			}

			// Fixed deltaTime to avoid non-physics behavior
			float targetDeltaTime = 1.0f / m_targetFrameRate;
			accumulatedTime += m_tickClock.restart();

			if (accumulatedTime.asSeconds() >= targetDeltaTime)
			{
				accumulatedTime -= sf::seconds(targetDeltaTime);
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return m_window.getSize();
	}

	void Application::Quit()
	{
		m_window.close();
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (m_currentWorld)
			m_currentWorld->TickInternal(deltaTime);

		TimerManager::Instance().UpdateTimer(deltaTime);
		PhysicsSystem::Instance().Step(deltaTime);

		// We need to clean up assets which are not in use anymore.
		// Also we need to call Clean method for current world.
		// We do it after all tick logic is happened.
		if (m_cleanCycleClock.getElapsedTime() >= m_cleanCycleInterval)
		{
			m_cleanCycleClock.restart();
			AssetManager::Instance().Clean();

			if (m_currentWorld)
				m_currentWorld->Clean();
		}

		if (m_pendingWorld && m_pendingWorld != m_currentWorld)
		{
			m_currentWorld = m_pendingWorld;
			PhysicsSystem::Instance().CleanUp();
			m_currentWorld->BeginPlayInternal();
		}
	}

	void Application::Tick(float deltaTime) {}

	bool Application::DispatchEvent(const sf::Event& event)
	{
		if (m_currentWorld)
		{
			return m_currentWorld->DispatchEvent(event);
		}

		return false;
	}

	void Application::Render()
	{
		if (!m_currentWorld)
			return;

		m_currentWorld->Render(m_window);
	}

	void Application::RenderInternal()
	{
		m_window.clear(sf::Color::Black);
		Render();
		m_window.display();
	}
}
