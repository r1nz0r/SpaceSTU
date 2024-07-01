#pragma once

#include "Gameplay/GameStage.h"

namespace SSTU
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* owner, float waitDuration = 5.f);
		virtual void Start() override;

	private:
		float m_waitDuration;
	};
}