#pragma once
#include "Gameplay/GameStage.h"
#include "SFML/Graphics.hpp"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);
		virtual void Start() override;

	private:
		float m_spawnInterval;
		float m_switchInterval;
		float m_spawnDistanceToEdge;

		sf::Vector2f m_leftSpawnLocation;
		sf::Vector2f m_rightSpawnLocation;
		sf::Vector2f m_spawnLocation;

		TimerHandler m_spawnTimerHandler;
		TimerHandler m_switchTimerHandler;

		int m_rowsToSpawn;
		int m_spawnedRowsCount;

		int m_vanguardsPerRow;
		int m_spawnedVanguardsCount;

		virtual void Finish() override;
		void SpawnVanguard();
		void SwitchRow();
	};
}