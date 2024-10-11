#pragma once
#include "Framework/World.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class PlayerSpaceship;
	class GameplayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owner);
	private:		
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* obj);
		void GameOver();
		virtual void OnAllGameStagesFinished() override;
		void Restart();
		void Quit();
		void SpawnCosmetics();

		std::weak_ptr<PlayerSpaceship> m_playerSpaseship;
		std::weak_ptr<GameplayHUD> m_gameplayHUD;
		TimerHandler m_timerHandler;
	};
}