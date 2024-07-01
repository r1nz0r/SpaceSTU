#pragma once
#include "Framework/Object.h"
#include "Framework/Delegate.h"

namespace SSTU
{
	class PlayerSpaceship;
	class World;
	class Player : public Object
	{
	public:
		Player();
		std::weak_ptr<PlayerSpaceship> SpawnSpaceship(World* world);
		const std::weak_ptr<PlayerSpaceship> GetSpaceship() const { return m_spaceship; };

		void AddLifes(unsigned int count);
		int GetLifes() const { return m_lifeCount; }

		void AddScore(unsigned int amt);
		int GetScore() const { return m_score; }

		Delegate<int> onLifeChanged;
		Delegate<int> onScoreChanged;
		Delegate<> onLifeExhausted;

	private:
		unsigned int m_lifeCount;
		unsigned int m_score;
		std::weak_ptr<PlayerSpaceship> m_spaceship;
	};
}