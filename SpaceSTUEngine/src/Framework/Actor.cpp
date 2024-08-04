#include "Framework/Actor.h"
#include "Framework/Core.h"
#include "Framework/AssetManager.h"
#include "Framework/MathUtility.h"
#include "Framework/World.h"
#include "Framework/Application.h"
#include "Framework/PhysicsSystem.h"
#include "box2d/b2_body.h"

namespace SSTU
{
	Actor::Actor(World* owner, const std::string& texturePath)
		: m_ownerWorld{ owner }
		, m_bBeganPlay{ false }
		, m_texture{}
		, m_sprite{}
		, m_physicsBody{nullptr}
		, m_bPhysicsEnabled{false}
		, m_teamId{GetNeutralTeamId()}

	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed!");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_bBeganPlay)
		{
			m_bBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingDestroy())
			return;

		Tick(deltaTime);
	}

	void Actor::BeginPlay()
	{
		//LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor Ticking");
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_texture = AssetManager::Instance().LoadTexture(texturePath);
		//assert(m_texture);
		if (!m_texture)
			return;

		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{m_texture->getSize()}});
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window) const
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_sprite);
	}

	void Actor::SetLocation(const sf::Vector2f& location)
	{
		m_sprite.setPosition(location);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetRotation(float rotation)
	{
		m_sprite.setRotation(rotation);
		UpdatePhysicsBodyTransform();
	}

	sf::Vector2f Actor::GetLocation() const
	{
		return m_sprite.getPosition();
	}

	float Actor::GetRotation() const
	{
		return m_sprite.getRotation();
	}

	void Actor::AddLocationOffset(const sf::Vector2f& offset)
	{
		SetLocation(GetLocation() + offset);
	}

	void Actor::AddRotationOffset(float offset)
	{
		SetRotation(GetRotation() + offset);
	}

	sf::Vector2f Actor::GetForwardVector() const
	{
		return Math::RotationToVector(GetRotation());
	}

	sf::Vector2f Actor::GetRightVector() const
	{
		return Math::RotationToVector(GetRotation() + 90.0f);
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bounds = m_sprite.getGlobalBounds();
		m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	}

	bool Actor::IsOutOfWindow(float allowance) const
	{
		sf::Vector2u windowSize = GetWorld()->GetApplication()->GetWindowSize();
		sf::FloatRect actorSize = GetGlobalBounds();
		sf::Vector2f actorLocation = GetLocation();

		if (actorLocation.x < -actorSize.width - allowance ||
			actorLocation.x > windowSize.x + actorSize.width + allowance ||
			actorLocation.y < -actorSize.height - allowance ||
			actorLocation.y > windowSize.y + actorSize.height + allowance
			)
		{
			return true;
		}
		
		return false;
	}

	void Actor::SetEnablePhysics(bool bState)
	{
		m_bPhysicsEnabled = bState;
		m_bPhysicsEnabled ? EnablePhysics() : DisablePhysics();
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (!m_physicsBody)
			return;

		float physicsScale = PhysicsSystem::Instance().GetPhysicsScale();
		b2Vec2 position { GetLocation().x * physicsScale, GetLocation().y * physicsScale };
		float rotation = Math::DegreesToRadians(GetRotation());

		m_physicsBody->SetTransform(position, rotation);
	}

	void Actor::OnBeginOverlap(Actor* other)
	{
		LOG("Overlaped");
	}

	void Actor::OnEndOverlap(Actor* other)
	{
		LOG("End overlap");
	}

	void Actor::Destroy()
	{
		DisablePhysics();
		onActorDestroyed.Notify(this);
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (!other || GetTeamId() == GetNeutralTeamId() || other->GetTeamId() == GetNeutralTeamId())
			return false;

		return GetTeamId() != other->GetTeamId();
	}

	void Actor::ApplyDamage(float amount)
	{

	}

	void Actor::EnablePhysics()
	{
		if (m_physicsBody)
			return;

		m_physicsBody = PhysicsSystem::Instance().AddListener(this);
	}
	void Actor::DisablePhysics()
	{
		if (!m_physicsBody)
			return;

		PhysicsSystem::Instance().RemoveListener(m_physicsBody);
		m_physicsBody = nullptr;
	}
}

