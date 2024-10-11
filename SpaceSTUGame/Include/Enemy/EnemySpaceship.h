#pragma once
#include "Framework/Core.h"
#include "SpaceShip/SpaceShip.h"
#include "Player/Reward.h"

namespace SSTU
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(
			World* owner,
			const std::string& texturePath,
			float collisionDamage = 200.0f,
			float rewardSpawnWeight = 0.5f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreewayShooterReward,
				CreateFrontalWiperReward,
				CreateLifeReward
			}
		);
		virtual void Tick(float deltaTime);
		void SetScoreReward(int amount);
		void SetRewardSpawnWeight(float weight);

	private:
		void SpawnReward();
		virtual void OnBeginOverlap(Actor* actor) override;
		virtual void OnBlow() override;

		float m_collisionDamage;
		int m_scoreReward;
		float m_rewardSpawnWeight;

		List<RewardFactoryFunc> m_rewardFactories;
	};
}