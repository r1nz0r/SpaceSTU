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
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreewayShooterReward,
				CreateFrontalWiperReward
			}
		);
		virtual void Tick(float deltaTime);
	private:
		void SpawnReward();
		float m_collisionDamage;
		virtual void OnBeginOverlap(Actor* actor) override;
		virtual void OnBlow() override;
		List<RewardFactoryFunc> m_rewardFactories;
	};
}