#pragma once

#include "Framework/Object.h"
#include "Framework/Delegate.h"

namespace SSTU
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* owner);
		const World* GetWorld() const { return m_world; }
		World* GetWorld() { return m_world; }

		Delegate<> onStageFinished;

		virtual void Start();
		virtual void Tick(float deltaTime);
		void Finish();
		bool IsStageFinished() const { return m_bIsStageFinished; }

	private:
		World* m_world;
		bool m_bIsStageFinished;
		virtual void OnStageFinished();
	};
}