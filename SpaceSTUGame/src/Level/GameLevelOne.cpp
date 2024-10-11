#include "Gameplay/WaitStage.h"
#include "Level/GameLevelOne.h"
#include "Widgets/GameplayHUD.h"
#include "Framework/Application.h"

#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"

#include "Player/PlayerSpaceship.h"
#include "Player/PlayerManager.h"


namespace SSTU
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World(owner)
	{}

	void GameLevelOne::BeginPlay()
	{		
		Player& newPlayer = PlayerManager::Instance().CreateNewPlayer();
		m_playerSpaseship = newPlayer.SpawnSpaceship(this);
		m_playerSpaseship.lock()->onActorDestroyed.BindAction(GetWeakPtr(), &GameLevelOne::PlayerSpaceshipDestroyed);
		m_gameplayHUD = SpawnHUD<GameplayHUD>();

		m_gameplayHUD.lock()->GetRestartButtonDelegate().BindAction(GetWeakPtr(), &GameLevelOne::Restart);
		m_gameplayHUD.lock()->GetQuitButtonDelegate().BindAction(GetWeakPtr(), &GameLevelOne::Quit);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<GameStage>{new VanguardStage { this }});

		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<GameStage>{new TwinBladeStage { this }});

		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<GameStage>{new UFOStage { this }});

		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<GameStage>{new HexagonStage { this }});

		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<GameStage>{new ChaosStage { this }});

		AddStage(std::shared_ptr<GameStage>{new WaitStage { this, 6.f }});
		AddStage(std::shared_ptr<GameStage>{new BossStage { this }});
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* obj)
	{
		m_playerSpaseship = PlayerManager::Instance().GetPlayer()->SpawnSpaceship(this);

		if (!m_playerSpaseship.expired())		
			m_playerSpaseship.lock()->onActorDestroyed.BindAction(GetWeakPtr(), &GameLevelOne::PlayerSpaceshipDestroyed);
		else
			GameOver();
	}

	void GameLevelOne::GameOver()
	{
		if (!m_gameplayHUD.expired())
			m_gameplayHUD.lock()->OnGameFinished(false);

		LOG("Game Over!===========================");
	}

	void GameLevelOne::OnAllGameStagesFinished()
	{
		if (!m_gameplayHUD.expired())
			m_gameplayHUD.lock()->OnGameFinished(true);
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Instance().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::Quit()
	{
		GetApplication()->Quit();
	}
}