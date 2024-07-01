#pragma once
#include "Framework/Core.h"
#include "Player/Player.h"
#include "Framework/NonCopyable.h"

namespace SSTU
{
	class PlayerManager : private NonCopyable
	{
	public:
		Player& CreateNewPlayer();
		Player* GetPlayer(int playerIndex = 0);
		const Player* GetPlayer(int playerIndex = 0) const;
		static PlayerManager& Instance();
		void Reset();
	protected:
		PlayerManager();

	private:
		List<Player> m_players;
		static std::unique_ptr<PlayerManager> instance;
	};
}