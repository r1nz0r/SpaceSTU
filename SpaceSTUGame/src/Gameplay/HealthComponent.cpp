#include "Gameplay/HealthComponent.h"
#include "Framework/Core.h"

namespace SSTU
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: m_health { health }
		, m_maxHealth { maxHealth }
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

		onHealthChanged.Notify(amount, m_health, m_maxHealth);

		if (amount < 0)
		{
			TakeDamage(-amount);
			if (m_health <= 0)
			{
				OnHealthEmpty();
			}
		}
	}

	void HealthComponent::SetInitialHealth(float health, float maxHealth)
	{
		m_health = health;
		m_maxHealth = maxHealth;
	}

	void HealthComponent::TakeDamage(float amount)
	{
		onTakenDamage.Notify(amount, m_health, m_maxHealth);
	}

	void HealthComponent::OnHealthEmpty()
	{
		onHealthEmpty.Notify();
	}
}
