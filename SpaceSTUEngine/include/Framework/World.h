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

		template<typename ActorType>
		std::weak_ptr<ActorType> SpawnActor();

	private:
		void Tick(float deltaTime);
		void BeginPlay();

		Application* m_ownerApp;
		bool m_bBeganPlay;

		List<std::shared_ptr<Actor>> m_actors;
		List<std::shared_ptr<Actor>> m_pendingActors;
	};

	template<typename ActorType>
	std::weak_ptr<ActorType> World::SpawnActor()
	{
		static_assert(std::is_base_of<Actor, ActorType>::value, "ActorType must derive from Actor");
		auto newActor = std::make_shared<ActorType>(this);
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}