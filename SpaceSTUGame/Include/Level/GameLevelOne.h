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
		std::weak_ptr<PlayerSpaceship> m_playerSpaseship;
		std::weak_ptr<GameplayHUD> m_gameplayHUD;
		TimerHandler m_timerHandler;
		
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* obj);
		void GameOver();
	};
}