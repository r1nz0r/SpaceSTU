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

		int GetCurrentLevel() const { return m_currentLevel; }
		int GetMaxLevel() const { return m_maxLevel; }

		virtual void IncrementLevel(int amount = 1);
	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootImpl() = 0;
		Actor* m_owner;

		int m_currentLevel;
		int m_maxLevel;
	};
}