#include "Enemy/BossStage.h"
#include "Enemy/Boss.h"
#include "Framework/World.h"
#include "Framework/Application.h"

namespace SSTU
{
	BossStage::BossStage(World* world)
		: GameStage(world)
	{}

	void BossStage::Start()
	{
		std::weak_ptr<Boss> boss = GetWorld()->SpawnActor<Boss>();
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		boss.lock()->SetLocation({windowSize.x / 2.f, 200.f});
		boss.lock()->onActorDestroyed.BindAction(GetWeakPtr(), &BossStage::BossDestroyed);
	}

	void BossStage::BossDestroyed(Actor* bossActor)
	{
		FinishInternal();
	}
}