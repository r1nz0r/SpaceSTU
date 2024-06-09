#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"
#include "config.h"

SSTU::Application* GetApplication()
{
	return new SSTU::GameApplication();
}

namespace SSTU
{
	GameApplication::GameApplication()
		: Application { 600, 980, "Space STU", sf::Style::Titlebar | sf::Style::Close}
	{
		counter = 0;
		auto world = LoadWorld<World>();
		
		if (world.expired())
			return;

		//world.lock()->SpawnActor<Actor>();
		actorToDestroy = world.lock()->SpawnActor<Actor>();
		actorToDestroy.lock()->SetTexture(GetResourceDir() + R"(SpaceShooterRedux/PNG/playerShip2_red.png)");
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;

		if (counter >= 2.0f)
		{
			if (!actorToDestroy.expired())
				actorToDestroy.lock()->Destroy();
		}
	}
}