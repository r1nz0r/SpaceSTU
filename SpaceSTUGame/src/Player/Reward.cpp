#include "framework/world.h"
#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
//#include "Player/PlayerManager.h"

namespace SSTU
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		: Actor { world, texturePath },
		mRewardFunc { rewardFunc },
		mSpeed { speed }
	{}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablephysics(true);
	}
	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::OnBeginOverlap(Actor* otherActor)
	{
		if (!otherActor || otherActor->IsPendingDestroy())
			return;

		//if (!PlayerManager::Get().GetPlayer())
		//	return;

		//weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();
		//if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestory())
		//	return;

		//if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		//{
		//	
		//}

		PlayerSpaceship* playerSpaceship = dynamic_cast<PlayerSpaceship*>(otherActor);
		if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceship);
			Destroy();
		}
	}

	std::weak_ptr<Reward>CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	std::weak_ptr<Reward>CreateThreewayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreewayShooter);
	}

	std::weak_ptr<Reward>CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	//std::weak_ptr<Reward>CreateLifeReward(World* world)
	//{
	//	return CreateReward(world, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLife);
	//}

	std::weak_ptr<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		std::weak_ptr<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;

		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreewayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(std::unique_ptr<Shooter>{new ThreeWayShooter { player, sf::seconds(0.4f), {50.f, 0.f} }});
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(std::unique_ptr<Shooter>{new FrontalWiper { player, sf::seconds(0.4f), {50.f, 0.f} }});
		}
	}

	//void RewardLife(PlayerSpaceship* player)
	//{
	//	if (!PlayerManager::Get().GetPlayer())
	//		return;

	//	PlayerManager::Get().GetPlayer()->AddLifeCount(1);
	//}
}