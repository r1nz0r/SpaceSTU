#pragma once

#include <functional>
#include "Framework/Actor.h"

namespace SSTU
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<std::weak_ptr<Reward>(World*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
	private:
		virtual void OnBeginOverlap(Actor* otherActor) override;
		float m_speed;
		RewardFunc mRewardFunc;
	};

	std::weak_ptr<Reward> CreateHealthReward(World* world);
	std::weak_ptr<Reward> CreateThreewayShooterReward(World* world);
	std::weak_ptr<Reward> CreateFrontalWiperReward(World* world);
	std::weak_ptr<Reward> CreateLifeReward(World* world);

	std::weak_ptr<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreewayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
	void RewardLife(PlayerSpaceship* player);
}