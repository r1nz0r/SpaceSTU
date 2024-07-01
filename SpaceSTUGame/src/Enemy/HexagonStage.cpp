#include "Enemy/Hexagon.h"
#include "Enemy/HexagonStage.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	HexagonStage::HexagonStage(World* world)
		: GameStage { world },
		m_spawnInterval { 5.f },
		m_spawnSideOffset { 80.f },
		m_spawnGroupAmount { 5 },
		m_spawnedCounter { 0 },
		m_midSpawnLocation { world->GetApplication()->GetWindowSize().x / 2.f, -100.f },
		m_rightSpawnLocation { world->GetApplication()->GetWindowSize().x / 2.f + m_spawnSideOffset, -100.f - m_spawnSideOffset },
		m_leftSpawnLocation { world->GetApplication()->GetWindowSize().x / 2.f - m_spawnSideOffset, -100.f - m_spawnSideOffset }
	{}

	void HexagonStage::Start()
	{
		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &HexagonStage::SpawnHexagon, m_spawnInterval, true);
	}

	void HexagonStage::Finish()
	{
		TimerManager::Instance().ClearTimer(m_spawnTimer);
	}

	void HexagonStage::SpawnHexagon()
	{
		std::weak_ptr<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetLocation(m_midSpawnLocation);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetLocation(m_leftSpawnLocation);
		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetLocation(m_rightSpawnLocation);

		if (++m_spawnedCounter == m_spawnGroupAmount)
		{
			FinishInternal();
		}
	}
}