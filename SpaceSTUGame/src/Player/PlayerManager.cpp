#include "Player/PlayerManager.h"

namespace SSTU
{
	std::unique_ptr<PlayerManager> PlayerManager::instance { nullptr };
	PlayerManager::PlayerManager()
	{}

	Player& PlayerManager::CreateNewPlayer()
	{
		m_players.emplace(m_players.begin(), Player());
		return m_players.back();
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{
		if (playerIndex >= 0 && playerIndex <= m_players.size())
			return &(m_players[playerIndex]);

		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		if (playerIndex >= 0 && playerIndex <= m_players.size())
			return &(m_players[playerIndex]);

		return nullptr;
	}

	PlayerManager& PlayerManager::Instance()
	{
		if (!instance)
		{
			instance = std::move(std::unique_ptr<PlayerManager>{new PlayerManager {}});
		}

		return *instance;
	}

	void PlayerManager::Reset()
	{
		m_players.clear();
	}
}