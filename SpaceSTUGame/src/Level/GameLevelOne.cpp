#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Player/PlayerSpaceship.h"

namespace SSTU
{
	GameLevelOne::GameLevelOne(Application* owner)
		: World(owner)
	{
		/*auto playerTest = SpawnActor<PlayerSpaceship>();
		playerTest.lock()->SetLocation({ 300.0f, 490.0f });
		playerTest.lock()->AddRotationOffset(-90.0f);

		for (int i = 0; i < 3; ++i)
		{
			auto testSpaceShip = SpawnActor<Vanguard>();
			testSpaceShip.lock()->SetLocation({ 120.0f*2*i + 50.0f, -50.0f * i });
		}*/		
	}

	void GameLevelOne::BeginPlay()
	{
		m_timerHandler = TimerManager::Instance().SetTimer(GetWeakPtr(), &GameLevelOne::TimerCallBack_Test, 2, true);
	}

	void GameLevelOne::TimerCallBack_Test()
	{
		LOG("Callback called!");
		TimerManager::Instance().ClearTimer(m_timerHandler);
	}
}