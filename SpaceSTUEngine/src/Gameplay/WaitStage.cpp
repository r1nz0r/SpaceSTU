#include "Gameplay/WaitStage.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	WaitStage::WaitStage(World* owner, float waitDuration)
		: GameStage { owner }
		, m_waitDuration { waitDuration }
	{}

	void WaitStage::Start()
	{
		TimerManager::Instance().SetTimer(GetWeakPtr(), &WaitStage::FinishInternal, m_waitDuration, false);
	}
}