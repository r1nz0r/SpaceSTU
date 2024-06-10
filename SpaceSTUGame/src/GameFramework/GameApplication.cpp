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

		actorToDestroy = world.lock()->SpawnActor<Actor>();
		actorToDestroy.lock()->SetTexture(GetResourceDir() + R"(SpaceShooterRedux/PNG/playerShip2_red.png)");
		actorToDestroy.lock()->SetLocation({ 300.0f, 490.0f });
		actorToDestroy.lock()->AddRotationOffset(90.0f);
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