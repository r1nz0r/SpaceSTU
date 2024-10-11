#include "Enemy/EnemySpaceship.h"
#include "Framework/MathUtility.h"
#include "Player/PlayerManager.h"

namespace SSTU
{
	EnemySpaceship::EnemySpaceship(
		World* owner,
		const std::string& texturePath,
		float collisionDamage,
		float rewardSpawnWeight,
		const List<RewardFactoryFunc> rewards
	)	: Spaceship(owner, texturePath)
		, m_collisionDamage (collisionDamage)
		, m_rewardFactories (rewards)
		, m_scoreReward (10)
		, m_rewardSpawnWeight (rewardSpawnWeight)
	{
		SetTeamId(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsOutOfWindow(std::max(GetGlobalBounds().width * 2.f, GetGlobalBounds().height * 2.f)))
			Destroy();
	}

	void EnemySpaceship::SetScoreReward(int amount)
	{}

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0 || weight > 1)
			return;

		m_rewardSpawnWeight = weight;
	}

	void EnemySpaceship::SpawnReward()
	{
		int pick = static_cast<int>(Math::RandomRange(0, m_rewardFactories.size()));

		if (m_rewardSpawnWeight < Math::RandomRange(0, 1))
			return;

		if (pick >= 0 && pick < m_rewardFactories.size())
		{
			auto newReward = m_rewardFactories[pick](GetWorld());
			newReward.lock()->SetLocation(GetLocation());
		}
	}

	void EnemySpaceship::OnBeginOverlap(Actor * other)
	{
		Spaceship::OnBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(m_collisionDamage);
		}
	}

	void EnemySpaceship::OnBlow()
	{
		SpawnReward();
		auto player = PlayerManager::Instance().GetPlayer();

		if (player)
			player->AddScore(m_scoreReward);
	}
}