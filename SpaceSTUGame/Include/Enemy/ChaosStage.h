#pragma once
#include <SFML/Graphics.hpp>
#include "Gameplay/GameStage.h"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* world);

		virtual void Start() override;

	private:
		virtual void Finish() override;
		void SpawnVanguard();
		void SpawnTwinBlade();
		void SpawnHexgon();
		void SpawnUFO();

		void IncreaseDifficulity();
		void OnStageDurationReached();

		sf::Vector2f GetRandomSpawnLocationTop() const;
		sf::Vector2f GetRandomSpawnLocationSide() const;

		float m_spawnInterval;
		float m_minSpawnInterval;

		float m_spawnIntervalDecrement;
		float m_spawnIntervalDecrmentInterval;

		float m_stageDuration;

		TimerHandler mDifficultTimerHandle;
		TimerHandler m_spawnTimer;
	};
}