#pragma once
#include <Framework/Core.h>
#include "SFML/Graphics.hpp"

namespace SSTU
{		
	class Actor;
	class Application;	
	class World
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

	private:
		void Tick(float deltaTime);
		void BeginPlay();

		Application* m_ownerApp;
		bool m_bBeganPlay;

		List<std::shared_ptr<Actor>> m_actors; // Actual actors in world
		List<std::shared_ptr<Actor>> m_pendingActors; // Actor to be spawned in next tick
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