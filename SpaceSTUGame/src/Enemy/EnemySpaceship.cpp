#include "Enemy/EnemySpaceship.h"
#include "Framework/MathUtility.h"
namespace SSTU
{
	EnemySpaceship::EnemySpaceship(
		World* owner,
		const std::string& texturePath,
		float collisionDamage,
		const List<RewardFactoryFunc> rewards
	)	: Spaceship(owner, texturePath)
		, m_collisionDamage {collisionDamage}
		, m_rewardFactories {rewards}
	{
		SetTeamId(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsOutOfWindow(std::max(GetGlobalBounds().width * 2.f, GetGlobalBounds().height * 2.f)))
			Destroy();
	}

	void EnemySpaceship::SpawnReward()
	{
		int pick = static_cast<int>(Math::RandomRange(0, m_rewardFactories.size()));

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
	}
}