#pragma once
#include "Gameplay/GameStage.h"

namespace SSTU
{
	class Actor;
	class BossStage : public GameStage
	{
	public:
		BossStage(World* world);
		virtual void Start() override;

	private:
		void BossDestroyed(Actor* bossActor);
	};
}