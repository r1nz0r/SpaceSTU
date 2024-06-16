#pragma once
#include "Framework/Delegate.h"

namespace SSTU
{
	class HealthComponent
	{
	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amount);
		float GetHealth() const { return m_health; }
		float GetMaxHealth() const { return m_maxHealth; }
		
		Delegate<float, float, float> onHealthChanged;

	private:
		void TakeDamage(float amount);
		void OnHealthEmpty();
		void HealthRegen(float amount);
		float m_health;
		float m_maxHealth;
	};
}