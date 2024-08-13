#pragma once
#include "Widgets/HUD.h"
#include "Widgets/Button.h"
#include "Widgets/TextWidget.h"

namespace SSTU
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();
		virtual void Draw(sf::RenderWindow& window) override;
		virtual bool HandleEvent(const sf::Event& event) override;
		virtual void Tick(float deltaTime) override;

		Delegate<>& GetStartButtonDelegate() { return m_startButton.onClicked; }
		Delegate<>& GetQuitButtonDelegate() { return m_quitButton.onClicked; }

	private:
		virtual void Init(const sf::RenderWindow& window) override;
		TextWidget m_titleText;
		Button m_startButton;
		Button m_quitButton;
	};
}