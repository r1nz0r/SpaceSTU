#pragma once
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace SSTU
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* world);
		virtual void Start() override;
	private:
		virtual void Finish() override;
		sf::Vector2f GetRandomSpawnLoc() const;
		void SpawnUFO();

		float mSpawnInterval;
		int mSpawnAmt;
		int mCurrentSpawnAmt;
		float mUFOSpeed;

		TimerHandler mSpawnTimer;
	};
}