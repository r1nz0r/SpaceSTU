#pragma once
#include "Framework/World.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owner);
	private:
		virtual void BeginPlay() override;
		std::weak_ptr<PlayerSpaceship> playerTest;
		void TimerCallBack_Test();

		TimerHandler m_timerHandler;
	};
}