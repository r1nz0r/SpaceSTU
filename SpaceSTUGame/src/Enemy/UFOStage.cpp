#include "Enemy/UFOStage.h"
#include "Enemy/UFO.h"
#include "Framework/Application.h"
#include "Framework/MathUtility.h"
#include "Framework/World.h"
#include "Weapon/BulletShooter.h"

namespace SSTU
{
	UFOStage::UFOStage(World* world)
		: GameStage { world },
		mSpawnInterval { 4.f },
		mSpawnAmt { 10 },
		mCurrentSpawnAmt { 0 },
		mUFOSpeed { 200.f }
	{

	}

	void UFOStage::Start()
	{
		mSpawnTimer = TimerManager::Instance().SetTimer(GetWeakPtr(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::Finish()
	{
		TimerManager::Instance().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLoc() const
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

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLoc();
		auto windowSize = GetWorld()->GetApplication()->GetWindowSize();
		sf::Vector2f center { windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f spawnLocToCenter { center.x - spawnLoc.x, center.y - spawnLoc.y };
		Math::NormalizeVector(spawnLocToCenter);

		sf::Vector2f spawnVelocity = spawnLocToCenter * mUFOSpeed;

		std::weak_ptr<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUFO.lock()->SetLocation(spawnLoc);

		if (++mCurrentSpawnAmt == mSpawnAmt)
		{
			FinishInternal();
		}
	}
}