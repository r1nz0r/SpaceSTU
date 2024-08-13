#pragma once
#include "Framework/World.h"

namespace SSTU
{
	class MainMenuHUD;
	class MainMenu : public World
	{
	public:
		MainMenu(Application* owner);
		virtual void BeginPlay() override;

	private:		
		std::weak_ptr<MainMenuHUD> m_mainMenuHUD;

		void StartGame();
		void QuitGame();
	};
}