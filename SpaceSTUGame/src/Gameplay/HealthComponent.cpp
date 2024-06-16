#include "Gameplay/HealthComponent.h"
#include "Framework/Core.h"

namespace SSTU
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: m_health{health}
		, m_maxHealth{maxHealth}
	{}

	void HealthComponent::ChangeHealth(float amount)
	{
		if (m_health <= 0 || amount == 0)
			return;

		m_health += amount;
		if (m_health < 0)
			m_health = 0;

		else if (m_health > m_maxHealth)
			m_health = m_maxHealth;

		if (amount < 0)
		{
			TakeDamage(-amount);
			if (m_health <= 0)
			{
				OnHealthEmpty();
			}
		}
		else
		{
			HealthRegen(amount);
		}
	}

	void HealthComponent::TakeDamage(float amount)
	{
		LOG("Took damage: %f, now health is: %f/%f", amount, m_health, m_maxHealth);
	}

	void HealthComponent::OnHealthEmpty()
	{
		LOG("Dead");
	}

	void HealthComponent::HealthRegen(float amount)
	{
		LOG("Heal: %f, now health is: %f/%f", amount, m_health, m_maxHealth);
	}
}
