#pragma once
#include "Widgets/HUD.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ProgressBar.h"
#include "Widgets/ImageWidget.h"

namespace SSTU
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void Tick(float deltaTime) override;

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
	};
}