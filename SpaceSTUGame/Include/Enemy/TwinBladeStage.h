#pragma once
#include "Gameplay/GameStage.h"
#include "SFML/Graphics.hpp"
#include "Framework/TimerManager.h"

namespace SSTU
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* owner);
		virtual void Start() override;
		

	private:
		void SpawnTwinBlade();
		virtual void Finish() override;

		float m_spawnInterval;
		float m_spawnDistanceToCenter;

		sf::Vector2f m_leftSpawnLocation;
		sf::Vector2f m_rightSpawnLocation;
		sf::Vector2f m_currentSpawnLocation;

		TimerHandler m_spawnTimerHandler;

		int m_spawnAmount;
		int m_spawnedCounter;
	};
}