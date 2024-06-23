#pragma once
#include "Framework/Core.h"
#include "Framework/NonCopyable.h"
#include "box2d/b2_world.h"

namespace SSTU
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener, private NonCopyable
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Instance();
		
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* listener);
		float GetPhysicsScale() const { return m_physicsScale; }

		static void CleanUp();

	private:
		PhysicsSystem();
		static std::unique_ptr<PhysicsSystem> instance;

		b2World m_physicsWorld;
		float m_physicsScale;
		int m_velocityIterations;
		int m_positionIterations;
		PhysicsContactListener m_contactListener;
		Set<b2Body*> m_pendingRemoveListeners;
		void ProcessRemoveListeners();
	};
}