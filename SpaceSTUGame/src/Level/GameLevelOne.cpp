#include "Gameplay/WaitStage.h"
#include "Level/GameLevelOne.h"
#include "Widgets/GameplayHUD.h"

#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/ChaosStage.h"

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
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(std::shared_ptr<ChaosStage>{new ChaosStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 1.f }});
		AddStage(std::shared_ptr<VanguardStage>{new VanguardStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 3.f }});
		AddStage(std::shared_ptr<TwinBladeStage>{new TwinBladeStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 3.f }});
		AddStage(std::shared_ptr<HexagonStage>{new HexagonStage { this }});

		AddStage(std::shared_ptr<WaitStage>{new WaitStage { this, 3.f }});
		AddStage(std::shared_ptr<UFOStage>{new UFOStage { this }});

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