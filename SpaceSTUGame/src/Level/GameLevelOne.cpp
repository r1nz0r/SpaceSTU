#include "Gameplay/WaitStage.h"
#include "Level/GameLevelOne.h"
#include "Widgets/GameplayHUD.h"
#include "Framework/Application.h"
#include "Framework/BackdropActor.h"
#include "Framework/BackgroundLayer.h"

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
		SpawnCosmetics();

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

	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/BackGrounds/blue.png");
		auto planets = SpawnActor<BackgroundLayer>();

		if (planets.expired())
			return;

		planets.lock()->SetAssets
		(
			{
				"SpaceShooterRedux/PNG/Planets/Planet1.png",
				"SpaceShooterRedux/PNG/Planets/Planet2.png",
				"SpaceShooterRedux/PNG/Planets/Planet3.png",
				"SpaceShooterRedux/PNG/Planets/Planet4.png",
				"SpaceShooterRedux/PNG/Planets/Planet5.png",
				"SpaceShooterRedux/PNG/Planets/Planet6.png",
				"SpaceShooterRedux/PNG/Planets/Planet7.png"
			}
		);

		planets.lock()->SetSpritesCount(3);
		planets.lock()->SetSizes(0.6f, 1.5f);
		planets.lock()->SetVelocities({ 0.f, 40.f }, { 0.f, 150.f });

		auto meteors = SpawnActor<BackgroundLayer>();

		if (meteors.expired())
			return;

		meteors.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
			}
		);

		meteors.lock()->SetSpritesCount(20);
		meteors.lock()->SetSizes(0.2f, 0.5f);
	}
}