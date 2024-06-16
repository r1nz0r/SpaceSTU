#pragma once

namespace SSTU
{
	class Actor;
	class Shooter
	{
	public:
		virtual ~Shooter() = default;
		void Shoot();
		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return m_owner; }

	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootImpl() = 0;
		Actor* m_owner;
	};
}