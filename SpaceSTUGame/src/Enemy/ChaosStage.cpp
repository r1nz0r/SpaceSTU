#include "Enemy/ChaosStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"

#include "Framework/MathUtility.h"
#include "Framework/World.h"
#include "Framework/Application.h"

#include "Weapon/BulletShooter.h"

namespace SSTU
{
	ChaosStage::ChaosStage(World* world)
		: GameStage { world },
		m_spawnInterval { 4.f },
		m_minSpawnInterval { 0.8f },
		m_spawnIntervalDecrement { 0.5f },
		m_spawnIntervalDecrmentInterval { 5.f },
		m_stageDuration { 60.f }
	{}

	void ChaosStage::Start()
	{
		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::SpawnVanguard, m_spawnInterval);
		mDifficultTimerHandle = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::IncreaseDifficulity, m_spawnIntervalDecrmentInterval, true);
		TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::OnStageDurationReached, m_stageDuration);
	}

	void ChaosStage::Finish()
	{
		TimerManager::Instance().ClearTimer(mDifficultTimerHandle);
		TimerManager::Instance().ClearTimer(m_spawnTimer);
	}
	void ChaosStage::SpawnVanguard()
	{
		std::weak_ptr<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetLocation(GetRandomSpawnLocationTop());
		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::SpawnTwinBlade, m_spawnInterval);
	}
	void ChaosStage::SpawnTwinBlade()
	{
		std::weak_ptr<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetLocation(GetRandomSpawnLocationTop());
		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::SpawnHexgon, m_spawnInterval);
	}

	void ChaosStage::SpawnHexgon()
	{
		std::weak_ptr<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetLocation(GetRandomSpawnLocationTop());
		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::SpawnUFO, m_spawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{

		sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		sf::Vector2f center = sf::Vector2f { windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f dirToCenter = center - spawnLoc;
		Math::NormalizeVector(dirToCenter);

		std::weak_ptr<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.f);
		newUFO.lock()->SetLocation(spawnLoc);

		m_spawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &ChaosStage::SpawnVanguard, m_spawnInterval);
	}

	void ChaosStage::IncreaseDifficulity()
	{
		m_spawnInterval -= m_spawnIntervalDecrement;

		if (m_spawnInterval < m_minSpawnInterval)
		{
			m_spawnInterval = m_minSpawnInterval;
		}
	}

	void ChaosStage::OnStageDurationReached()
	{
		Finish();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		float spawnX = Math::RandomRange(100.f, windowSize.x - 100.f);
		float spawnY = -100.f;

		return { spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		float spawnLeft = Math::RandomRange(-1, 1);
		float spawnLocX = 0;

		if (spawnLeft < 0)
		{
			spawnLocX = windowSize.x + 100.f;
		}
		else
		{
			spawnLocX = -100.f;
		}

		float spawnLocY = Math::RandomRange(0, windowSize.y);
		return sf::Vector2f { spawnLocX, spawnLocY };
	}
}