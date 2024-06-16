#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Framework/AssetManager.h"
#include "Player/PlayerSpaceship.h"
#include "config.h"

// Necessary for extern function definition in Engine/EntryPoint.h
SSTU::Application* GetApplication()
{
	return new SSTU::GameApplication();
}

namespace SSTU
{
	GameApplication::GameApplication()
		: Application { 600, 980, "Space STU", sf::Style::Titlebar | sf::Style::Close}
		, counter {0}
	{
		AssetManager::Instance().SetAssetRootDirectory(GetResourceDir());
		//counter = 0;
		auto world = LoadWorld<World>();
		
		if (world.expired())
			return;

		playerTest = world.lock()->SpawnActor<PlayerSpaceship>();
		playerTest.lock()->SetLocation({ 300.0f, 490.0f });
		playerTest.lock()->AddRotationOffset(-90.0f);
		auto testSpaceShip = world.lock()->SpawnActor<Spaceship>();
		testSpaceShip.lock()->SetTexture(R"(SpaceShooterRedux/PNG/playerShip2_red.png)");
		testSpaceShip.lock()->SetLocation({100.0f, 50.0f});
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;

		if (counter >= 3.0f)
		{
			if (!playerTest.expired())
				playerTest.lock()->Destroy();
		}
	}
}