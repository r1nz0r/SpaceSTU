#include "GameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "Framework/AssetManager.h"
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
	{
		AssetManager::Instance().SetAssetRootDirectory(GetResourceDir());
		//counter = 0;
		auto world = LoadWorld<GameLevelOne>();		
	}
}