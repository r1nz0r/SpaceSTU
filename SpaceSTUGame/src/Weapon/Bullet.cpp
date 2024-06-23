#include "Weapon/Bullet.h"

namespace SSTU
{
	Bullet::Bullet(
		World* world,
		Actor* owner,
		const std::string& texturePath,
		float speed,
		float damage
	)
		: Actor(world, texturePath)
		, m_owner(owner)
		, m_speed(speed)
		, m_damage(damage)
	{
		SetTeamId(owner->GetTeamId());
	}

	void Bullet::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void Bullet::SetDamage(float damage)
	{
		if (damage >= 0)
			m_damage = damage;
		else
			m_damage = 0;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);

		if (IsOutOfWindow())
			Destroy();
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablephysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		AddLocationOffset(GetForwardVector() * m_speed * deltaTime);
	}
	void Bullet::OnBeginOverlap(Actor* other)
	{
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(GetDamage());
			Destroy();
		}
	}
}