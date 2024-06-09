#include "Framework/Application.h"
#include "Framework/Core.h"
#include "Framework/World.h"
#include "Framework/AssetManager.h"

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
					m_window.close();
				}
			}

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

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (m_currentWorld)
			m_currentWorld->TickInternal(deltaTime);

		if (m_cleanCycleClock.getElapsedTime() >= m_cleanCycleInterval)
		{
			m_cleanCycleClock.restart();
			AssetManager::Instance().Clean();
		}
	}

	void Application::Tick(float deltaTime)
	{
		//LOG("Ticking at framerate: %f", 1.f / deltaTime);
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