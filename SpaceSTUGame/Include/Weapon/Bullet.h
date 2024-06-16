#pragma once
#include "Framework/Actor.h"

namespace SSTU
{
	class Bullet : public Actor
	{
	public:
		Bullet(
			World* world,
			Actor* owner,
			const std::string& texturePath,
			float speed = 500.f,
			float damage = 10.f
		);

		void SetSpeed(float speed);
		void SetDamage(float damage);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay();
	private:
		void Move(float deltaTime);

		Actor* m_owner;
		float m_speed;
		float m_damage;
	};
}