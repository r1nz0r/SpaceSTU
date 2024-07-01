#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/TimerManager.h"
#include "Gameplay/GameStage.h"

namespace SSTU
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* world);

		virtual void Start() override;
	private:
		virtual void Finish() override;
		void SpawnHexagon();

		float m_spawnInterval;
		float m_spawnSideOffset;
		int m_spawnGroupAmount;
		int m_spawnedCounter;

		sf::Vector2f m_midSpawnLocation;
		sf::Vector2f m_leftSpawnLocation;
		sf::Vector2f m_rightSpawnLocation;

		TimerHandler m_spawnTimer;
	};
}