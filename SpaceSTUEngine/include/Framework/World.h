#pragma once
#include <Framework/Core.h>
#include "SFML/Graphics.hpp"
#include "Framework/Object.h"

namespace SSTU
{		
	class Actor;
	class Application;	
	class GameStage;
	class World : public Object
	{
	public:
		World(Application* ownerApp);
		virtual ~World() = default;
	
		void TickInternal(float deltaTime);
		void BeginPlayInternal();
		void Render(sf::RenderWindow& window);

		template<typename ActorType, typename... Args>
		std::weak_ptr<ActorType> SpawnActor(Args... args);
		Application* GetApplication() const { return m_ownerApp; }
		
		void Clean();
		void AddStage(const std::shared_ptr<GameStage>& newStage);

	private:
		virtual void Tick(float deltaTime);
		virtual void BeginPlay();

		Application* m_ownerApp;
		bool m_bBeganPlay;

		List<std::shared_ptr<Actor>> m_actors; // Actual actors in world
		List<std::shared_ptr<Actor>> m_pendingActors; // Actor to be spawned in next tick
		List <std::shared_ptr<GameStage>> m_gameStages;

		List<std::shared_ptr<GameStage>>::iterator m_currentStage;

		virtual void InitGameStages();
		virtual void OnAllGameStagesFinished();
		void SetNextGameStage();
		void StartStages();
	};

	template<typename ActorType, typename... Args>
	std::weak_ptr<ActorType> World::SpawnActor(Args... args)
	{
		static_assert(std::is_base_of<Actor, ActorType>::value, "ActorType must derive from Actor");
		auto newActor = std::make_shared<ActorType>(this, args...);
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}