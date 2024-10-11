#include "Enemy/TwinBladeStage.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Enemy/TwinBlade.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	TwinBladeStage::TwinBladeStage(World* owner)
		: GameStage(owner)
		, m_spawnInterval{1.5f}
		, m_spawnDistanceToCenter{100.f}
		, m_leftSpawnLocation{}
		, m_rightSpawnLocation{}
		, m_amountToSpawn{4}
		, m_spawnedCounter{0}
	{
		auto windowSize = owner->GetApplication()->GetWindowSize();
		m_leftSpawnLocation = sf::Vector2f { windowSize.x / 2.f - m_spawnDistanceToCenter, -100.f };
		m_rightSpawnLocation = sf::Vector2f { windowSize.x / 2.f + m_spawnDistanceToCenter, -100.f };
		m_currentSpawnLocation = m_leftSpawnLocation;
	}

	void TwinBladeStage::Start()
	{
		m_spawnTimerHandler = TimerManager::Instance().SetTimer(GetWeakPtr(), &TwinBladeStage::SpawnTwinBlade, m_spawnInterval, true);
	}

	void TwinBladeStage::SpawnTwinBlade()
	{
		std::weak_ptr<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetLocation(m_currentSpawnLocation);
		m_currentSpawnLocation = m_currentSpawnLocation == m_leftSpawnLocation ? m_rightSpawnLocation : m_leftSpawnLocation;
		++m_spawnedCounter;

		if (m_spawnedCounter == m_amountToSpawn)
			FinishInternal();
	}

	void TwinBladeStage::Finish()
	{
		GameStage::Finish();
		TimerManager::Instance().ClearTimer(m_spawnTimerHandler);
	}
}