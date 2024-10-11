#pragma once
#include "Widgets/HUD.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ProgressBar.h"
#include "Widgets/ImageWidget.h"
#include "Widgets/Button.h"

namespace SSTU
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;
		void OnGameFinished(bool bHasPlayerWin);
		Delegate<>& GetRestartButtonDelegate() { return m_restartButton.onClicked; }
		Delegate<>& GetQuitButtonDelegate() { return m_quitButton.onClicked; }

	protected:
		virtual void Init(const sf::RenderWindow& window) override;
	private:
		void OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void OnPlayerSpaceshipDestroyed(Actor* actor);
		void RefreshHealthbar();
		void ConnectPlayerStats();
		void OnPlayerLifesChanged(int amount);
		void OnPlayerScoreChanged(int amount);

		TextWidget m_frameRateText;
		ProgressBar m_playerHealthBar;
		ImageWidget m_playerLifesIcon;
		TextWidget m_playerLifesText;

		ImageWidget m_playerScoreIcon;
		TextWidget m_playerScoreText;

		sf::Color m_healtyHealtbarColor;
		sf::Color m_criticalHealthbarColor;
		float m_criticalThreshold;

		float m_widgetSpacing;

		TextWidget m_winLoseText;
		TextWidget m_finalScoreText;
		Button m_restartButton;
		Button m_quitButton;

		sf::Vector2u m_windowSize;
	};
}