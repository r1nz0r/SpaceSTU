#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Player/PlayerSpaceship.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Gameplay/WaitStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Player/PlayerManager.h"
#include "Widgets/GameplayHUD.h"

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
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<VanguardStage>{new VanguardStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 5.f }});
		AddStage(std::shared_ptr<HexagonStage>{new HexagonStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 5.f }});
		AddStage(std::shared_ptr<UFOStage>{new UFOStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 3.f }});
		AddStage(std::shared_ptr<TwinBladeStage>{new TwinBladeStage { this }});
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
		LOG("Game Over!===========================");
	}
}