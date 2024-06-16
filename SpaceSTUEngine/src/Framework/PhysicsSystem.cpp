#include "Framework/PhysicsSystem.h"
#include "Framework/Actor.h"
#include "Framework/MathUtility.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"
#include <box2d/b2_contact.h>

namespace SSTU
{
	std::unique_ptr<PhysicsSystem> PhysicsSystem::instance = nullptr;

	PhysicsSystem::PhysicsSystem()
		: m_physicsWorld { b2Vec2_zero }
		, m_physicsScale { 0.01f }
		, m_velocityIterations { 8 }
		, m_positionIterations { 3 }
		, m_contactListener {}
		, m_pendingRemoveListeners {}		
	{
		m_physicsWorld.SetContactListener(&m_contactListener);
		m_physicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::ProcessRemoveListeners()
	{
		for (auto& listener : m_pendingRemoveListeners)		
			m_physicsWorld.DestroyBody(listener);
		
		m_pendingRemoveListeners.clear();
	}

	PhysicsSystem& PhysicsSystem::Instance()
	{
		if (!instance)
			instance.reset(new PhysicsSystem());

		return *instance;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessRemoveListeners();
		m_physicsWorld.Step(deltaTime, m_velocityIterations, m_positionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (!listener || listener->IsPendingDestroy())
			return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

		// We need to scale the position due to our physicsScale.
		auto scaledPosition = listener->GetLocation() * GetPhysicsScale();
		bodyDef.position.Set(scaledPosition.x, scaledPosition.y);
		bodyDef.angle = Math::DegreesToRadians(listener->GetRotation());

		b2Body* body = m_physicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bounds = listener->GetGlobalBounds();
		shape.SetAsBox(
			bounds.width / 2.0f * GetPhysicsScale(),
			bounds.height / 2.0f * GetPhysicsScale()
		);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);
		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		m_pendingRemoveListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::CleanUp()
	{
		instance.reset(new PhysicsSystem());
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		
		if (ActorA && !ActorA->IsPendingDestroy())		
			ActorA->OnActorBeginOverlap(ActorB);		

		if (ActorB && !ActorB->IsPendingDestroy())		
			ActorB->OnActorBeginOverlap(ActorA);
	}

	void PhysicsContactListener::EndContact(b2Contact * contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;
		
		if(contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	
		if (ActorA && !ActorA->IsPendingDestroy())
			ActorA->OnActorEndOverlap(ActorB);

		if (ActorB && !ActorB->IsPendingDestroy())
			ActorB->OnActorEndOverlap(ActorA);
	}
}