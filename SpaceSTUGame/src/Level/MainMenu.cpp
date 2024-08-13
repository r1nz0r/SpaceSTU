#include "Level/MainMenu.h"
#include "Widgets/MainMenuHUD.h"
#include "Framework/Application.h"
#include "Level/GameLevelOne.h"

namespace SSTU
{
	MainMenu::MainMenu(Application* owner)
		: World(owner)
	{
		m_mainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenu::BeginPlay()
	{
		m_mainMenuHUD.lock()->GetStartButtonDelegate().BindAction(GetWeakPtr(), &MainMenu::StartGame);
		m_mainMenuHUD.lock()->GetQuitButtonDelegate().BindAction(GetWeakPtr(), &MainMenu::QuitGame);
	}

	void MainMenu::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
		LOG("Start game!");
	}

	void MainMenu::QuitGame()
	{
		GetApplication()->Quit();
		LOG("Quit game!");
	}
}