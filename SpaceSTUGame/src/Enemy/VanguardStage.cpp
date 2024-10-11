#include "Enemy/VanguardStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	VanguardStage::VanguardStage(World* world)
		: GameStage { world }
		, m_spawnInterval { 2.1f }
		, m_switchInterval { 5.f }
		, m_spawnDistanceToEdge { 100.f }
		, m_leftSpawnLocation { 0.f, 0.f }
		, m_rightSpawnLocation { 0.f, 0.f }
		, m_spawnLocation { 0.f, 0.f }
		, m_rowsToSpawn { 2 }
		, m_spawnedRowsCount { 0 }
		, m_vanguardsPerRow { 5 }
		, m_spawnedVanguardsCount { 0 }
	{}

	void VanguardStage::Start()
	{
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		m_leftSpawnLocation = sf::Vector2f { m_spawnDistanceToEdge, -100.f };
		m_rightSpawnLocation = sf::Vector2f {windowSize.x - m_spawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::Finish()
	{
		TimerManager::Instance().ClearTimer(m_spawnTimerHandler);
		TimerManager::Instance().ClearTimer(m_switchTimerHandler);
	}

	void VanguardStage::SpawnVanguard()
	{
		auto newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetLocation(m_spawnLocation);
		++m_spawnedVanguardsCount;

		if (m_spawnedVanguardsCount == m_vanguardsPerRow)
		{
			TimerManager::Instance().ClearTimer(m_spawnTimerHandler);
			m_switchTimerHandler = TimerManager::Instance().SetTimer(GetWeakPtr(), &VanguardStage::SwitchRow, m_switchInterval, false);
			m_spawnedVanguardsCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (m_spawnedRowsCount == m_rowsToSpawn)
		{
			FinishInternal();
			return;
		}

		m_spawnLocation = m_spawnLocation == m_leftSpawnLocation ? m_rightSpawnLocation : m_leftSpawnLocation;
		m_spawnTimerHandler = TimerManager::Instance().SetTimer(GetWeakPtr(), &VanguardStage::SpawnVanguard, m_spawnInterval, true);
		++m_spawnedRowsCount;
	}
}