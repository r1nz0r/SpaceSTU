#include "Widgets/MainMenuHUD.h"

namespace SSTU
{
	MainMenuHUD::MainMenuHUD()
		: m_titleText("Light Years")
		, m_startButton("Start")
		, m_quitButton("Quit")
	{

	}

	void MainMenuHUD::Draw(sf::RenderWindow& window)
	{
		m_titleText.NativeDraw(window);
		m_startButton.NativeDraw(window);
		m_quitButton.NativeDraw(window);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		bool handled = false;

		// Check every single button for its event
		handled = m_quitButton.HandleEvent(event) || handled;
		handled = m_startButton.HandleEvent(event) || handled;

		// Return handled for any button was handle event or not
		return handled || HUD::HandleEvent(event);
	}

	void MainMenuHUD::Tick(float deltaTime)
	{}

	void MainMenuHUD::Init(const sf::RenderWindow& window)
	{
		m_titleText.SetTextSize(40);
		m_startButton.SetTextSize(20);
		m_quitButton.SetTextSize(20);	

		sf::Vector2u windowSize = window.getSize();
		m_titleText.SetLocation(sf::Vector2f(windowSize.x / 2.f, 100.f) - m_titleText.GetCenterPosition());
		m_startButton.SetLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f) - m_startButton.GetCenterPosition());
		m_quitButton.SetLocation(m_startButton.GetLocation() + sf::Vector2f {0.f, 50.f});
	}
}