#include "Gameplay/GameStage.h"
#include "Framework/Core.h"

namespace SSTU
{
	GameStage::GameStage(World* owner)
		: m_world(owner) 
		, m_bIsStageFinished{false}
	{}

	void GameStage::Start()
	{
		LOG("Stage Started!");
	}

	void GameStage::Tick(float deltaTime)
	{
		LOG("Stage Ticking!");
	}

	void GameStage::Finish()
	{
		onStageFinished.Notify();
		m_bIsStageFinished = true;
	}


}