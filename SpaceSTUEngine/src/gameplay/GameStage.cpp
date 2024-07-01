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

	}

	void GameStage::Tick(float deltaTime)
	{

	}

	void GameStage::FinishInternal()
	{
		m_bIsStageFinished = true;
		Finish();
		onStageFinished.Notify();
	}

	void GameStage::Finish()
	{
		LOG("Stage Finished!");
	}
}