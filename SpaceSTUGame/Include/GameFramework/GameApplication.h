#pragma once
#include "Framework/Application.h"
#include <memory>

namespace SSTU
{
	class Actor;
	class PlayerSpaceship;
	class GameApplication : public Application
	{
	public:
		GameApplication();
		virtual void Tick(float deltaTime) override;
	private:
		float counter;
		std::weak_ptr<PlayerSpaceship> playerTest;
	};
}