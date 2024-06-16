#include "Weapon/Shooter.h"

namespace SSTU
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImpl();
		}
	}
	Shooter::Shooter(Actor* owner)
		: m_owner(owner)
	{}
}